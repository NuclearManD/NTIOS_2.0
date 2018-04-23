#ifndef NTI_KERNEL_H
#define NTI_KERNEL_H
#pragma GCC diagnostic warning "-fpermissive"
//#pragma GCC diagnostic warning "-pedantic"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h" // for attachInterrupt, FALLING
#else
#include "WProgram.h"
#endif
#define CPU_ATMEL_NTISYS
char* substr(char* arr, int begin, int len);
void Nsystem(char* inp);
unsigned short len(char* d);
int freeRam();
int rows, cols;
byte data = 0;
byte selected=0;
bool term_opn=false;
byte term_y, term_x=0;
byte gui=0;
byte sel_process=0;
bool __redraw[40];
void (*reset)()=0;
void noprnt(char* x){}
void (*stdo)(char*)=noprnt;
void (*stde)(char*)=noprnt;
#define system Nsystem
#ifdef USE_CYRILLIC
#include "Cyrillic.h"//  include here for dependencies
#endif
#include <NMT_GFX.h>
#include <GEAR.h>
#include <SPI.h>
#include <SD.h>
#include "fs.h"
#include "kbd.h"
#include "basic.h"
GearControl gr;
NMT_GFX vga;
void term_close(){
  term_opn=false;
  term_y=0;
}
void term_print(char* d){
  vga.set_color(1);
  vga.print(d);
}
void term_error(char* d){
  vga.set_color(2);
  vga.print(d);
  vga.set_color(1);
}
char* hexchars="0123456789ABCDEF";
char* int_to_str(int i){
  char* o=malloc(5);
  o[0] = hexchars[(i >> 12) & 0xF];
  o[1] = hexchars[(i >> 8) & 0xF];
  o[2] = hexchars[(i >> 4) & 0xF];
  o[3] = hexchars[i & 0xF];
  o[4]=0;
  return o;
}
int exec_file(char* name){
  if(!sd_mounted){
    stde("No storage.");
    return 0;
  }
  char* data;
  char compiled[256];
  int length;
  File f=SD.open(name,FILE_READ);
  if(!f){
    stde("File not found!");
    return -1;
  }
  Serial.println(name+len(name)-3);
  if(!strcmpignorecase(name+len(name)-3,"BIN")){
    length=f.size();
    Serial.println(length);
    byte i=0;
    while (f.available()) {
      compiled[i]=(f.read());
      Serial.write(hexchars[15&(compiled[i]>>4)]);
      Serial.write(hexchars[compiled[i]&15]);
      i++;
    }
    Serial.println();
  }else{
    Serial.println("compiling basic...");
    data=malloc(f.size()+1);
    byte i=0;
    while (f.available()) {
      data[i]=(f.read());
      i++;
    }
    data[i]=0;
    length=compile(data,compiled);
    for(int i=0;i<length;i++){
      Serial.write(hexchars[15&(compiled[i]>>4)]);
      Serial.write(hexchars[compiled[i]&15]);
    }
    free(data);
    if(length==-1){
      stde("Compiler Error");
      return;
    }
  }
  f.close();
  setup_basic(stdo);
  return executeCompiledCode(compiled, length);
}
int freeRam() {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
/*char* substr(char* arr, int begin, int len)
{
    char* res = Nalloc(len+1);
    for (int i = 0; i < len; i++)
        res[i] = *(arr + begin + i);
    res[len] = 0;
    return res;
}*/
unsigned short len(char* d){
  unsigned short i=0;
  while(d[i]!=0)
    i++;
  return i;
}
int to_int(char* str){
  int out=0;
  for(byte i=0;i<len(str);i++){
    out+=pow(10,i)*(str[i]-'0');
  }
  return out;
}
void sw_gui(byte q){
  gui=q;
  for(byte i=0;i<40;i++)
    __redraw[i]=true;
}
char last_key=0;
bool shift_key=false;
char read(){
  if(gr.cprocess==sel_process)
    return last_key;
  else{
    return 0;
  }
}
bool available(){
  return (gr.cprocess==sel_process)&&(last_key!=0);
}
int launch(void (*a)(),void (*b)(),char* name="?", void (*c)()=__empty){
  //if(gr.cprocess==sel_process)
    sel_process=gr.addProcess(a,b,name,c,P_KILLER|P_KILLABLE);  // do this before addProcess() to get ID of next new process
  return sel_process;
}
void gear_stopwait(){
  for(byte i=0;i<gr.processes;i++){
    gr.ftimes[i]=millis()+gr.fupd_rate;
  }
  for(byte i=0;i<40;i++)
    __redraw[i]=true;
}
char* read(int* size, char* name){
  File f=SD.open(name);
  if(f){
    size[0]=f.size();
    char* ptr=(char*)malloc(size[0]);
    f.read(ptr, size[0]);
    f.close();
    return ptr;
  }else
    size[0]=-1;
  return (char*)8192;// 8192 is position of null-memory space.  Can't hurt memory that doesn't exist.
}
bool term_force=false;

char buf_0x10[256];

void Nsystem(char* inp){
  char* args[10];
  byte cnt=1;
  char* src=buf_0x10;
  args[0]=src;
  for(unsigned short i=0; i<len(inp); i++){
    char c=inp[i];
    if(c!=' ')
      src[i]=c;
    else{
      src[i]=0;
      args[cnt]=(char*)(i+1+(unsigned short)src);
      cnt++;
      while(inp[i+1]==' ')
        i++;
    }
  }
  src[len(inp)]=0;
  if(!strcmp(args[0],"terminate")){
    int pid=to_int(args[1]);
    if(pid>=gr.processes){
      stde("terminate : Bad PID");
    }else{
      int res=gr.kill(pid);
      if(res>=0)
        stdo("Process Killed");
      else if(res==ACCESS_DENIED){
        stde("Access Denied");
        if(term_force){
          stdo("\nCOMPUTER OVERRIDE; (danger!)\n");
          gr.__A_KILL(pid);
          stdo("Possible success.");
        }
      }else if(res==INVALID_ARGUMENT)
        stde("Invalid Argument");
      else{
        stde("Unknown Error ");
        stde(String(res).c_str());
      }
    }
  }else if(!strcmp(args[0],"lsps")){
    stdo(String(gr.processes).c_str());
    stdo(" Processes:");
    for(int i=0;i<gr.processes&&i<8;i++){
      stdo("\n :");
      stdo((String(i)+gr.getName(i)).c_str());
    }
  }else if(!strcmp(args[0],"sudo")){
    gr.p_perms[gr.cprocess]=0xFF;
    if(!strcmp(args[1],"-f")){
      term_force=true;
      stdo("Self-hacking ENABLED\n");
    }
    stdo("Gained all privleges.");
  }else if(!strcmp(args[0],"mount")){
    if(mount())
      stdo("Success.");
    else
      stde("Unknown Error.");
    kbd->begin(4, 2);
  }else if(!strcmp(args[0],"cls")){
    vga.set_cursor_pos(0,0);
    vga.clear();
    return; // escape newline
  }else if(!strcmp(args[0],"mem")){
    stdo("RAM bytes free: ");
    stdo(String(freeRam()).c_str());
  }else if(!strcmp(args[0],"dir")){
    if(!sd_mounted){
      stde("No SD card mounted.");
    }else{
      Serial.print("Opening directory ");
      Serial.println(curdir);
      File dir = SD.open(curdir);
      Serial.println("Rewinding directory...");
      dir.rewindDirectory();
      bool empty=true;
      while (true) {
        Serial.println("Opening next file...");
        File entry =  dir.openNextFile();
        Serial.print("Opened ");
        Serial.println(entry.name());
        if (! entry) {
          break;
        }
        empty=false;
        stdo(entry.name());
        if (entry.isDirectory()) {
          stdo("/\n");
        } else {
          // files have sizes, directories do not
          for(byte j=0;j<16-len(entry.name());j++)
            stdo(" ");
          stdo("0x");
          stdo(int_to_str(entry.size()));
          stdo("\n");
        }
        entry.close();
      }
      Serial.println("Done. Closing directory...");
      dir.close();
      Serial.println("Command complete.");
      if(empty){
        stdo("[directory empty]");
      }
    }
  }else if(!strcmp(args[0],"cd")){
    if(cnt<2){
      stde("Usage: cd directory");
    }else{
      Serial.print("Checking directory ");
      Serial.println(fs_resolve(args[1]));
      File f=SD.open(fs_resolve(args[1]));
      if(f&&f.isDirectory()){
        strcpy(curdir,fs_resolve_as_dir(args[1]));
        Serial.println("Valid.");
        f.close();
        goto nonewline;
      }
      stde("Not a directory: ");
      stde(fs_resolve(args[1]));
      Serial.println("Invalid.  Closing...");
      f.close();
    }
  }else if(!strcmp(args[0],"cat")){
    if(cnt<2){
      stde("Usage: cat file");
    }else{
      File f=SD.open(fs_resolve(args[1]));
      if(f&&!f.isDirectory()){
        char tmp[16];
        int i=0;
        while(f.available()){
          if(i==15){
            tmp[i]=0;
            stdo(tmp);
            i=0;
          }
          tmp[i]=f.read();
          i++;
        }
        tmp[i]=0;
        stdo(tmp);
        stdo("\r[end of file]");
        f.close();
      }else{
        stde("Not a file: ");
        stde(fs_resolve(args[1]));
      }
    }
  }else if(!strcmp(args[0],"hex")){
    if(cnt<2){
      stde("Usage: cat file");
    }else{
      File f=SD.open(fs_resolve(args[1]));
      if(f&&!f.isDirectory()){
        char tmp[34];
        int i=0;
        while(f.available()){
          if(i==32){
            tmp[i]=0;
            stdo(tmp);
            i=0;
          }
          byte c=f.read();
          tmp[i]=hexchars[c>>4];
          tmp[i+1]=hexchars[c&15];
          i+=2;
        }
        tmp[i]=0;
        stdo(tmp);
        stdo("\r[end of file]");
        f.close();
      }else{
        stde("Not a file: ");
        stde(fs_resolve(args[1]));
      }
    }
  }else if(!strcmp(args[0],"mkdir")){
    if(cnt<2)
      stde("Usage: mkdir [directory name]");
    else{
      stdo("creating directory ");
      stdo(fs_resolve(args[1]));
      stdo("...\r");
      if(!mkdir(args[1])){
        stde("Error creating ");
        stde(fs_resolve(args[1]));
      }
    }
  }else if(!strcmp(args[0],"!res")){
    if(cnt<2)
      Serial.println("Usage: !res [directory name]");
    else{
      Serial.print(args[1]);
      Serial.print(" : [");
      Serial.print(fs_resolve(args[1]));
      Serial.println("]");
    }
  }else if(!strcmp(args[0],"reboot")){
    asm volatile ("  jmp 0");
  }else if(!strcmp(args[0],"bc")){
    if(cnt<2)
      stde("Usage: bc [infile] (outfile)");
    else{
      File f=SD.open(fs_resolve(args[1]));
      if(f&&!f.isDirectory()){
        byte oname[64];
        if(cnt>2)
          strcpy(oname,args[2]);
        else{
          strcpy(oname,args[1]);
          int i;
          for(i=0;oname[i]!=0&&oname[i]!='.';i++);
          i++;
          strcpy(oname+i,"BIN");
        }
        File o=SD.open(fs_resolve(oname),O_WRITE | O_CREAT | O_TRUNC);
        if(o){
          byte* data=malloc(f.size()+1);
          byte compiled[256];
          int i=0;
          while (f.available()) {
            data[i]=(f.read());
            i++;
          }
          data[i]=0;
          int length=compile(data,compiled);
          free(data);
          for(int i=0;i<length;i++){
            Serial.write(hexchars[15&(compiled[i]>>4)]);
            Serial.write(hexchars[compiled[i]&15]);
            o.write(compiled[i]);
          }
          o.close();
        }else{
          stde("Error opening output file ");
          stde(oname);
        }
      }else
        stde("File does not exist!");
      f.close();
    }
  }else if(!strcmp(args[0],"help")){
    stdo(" : ALL commands MUST be lowercase.\n* Commands: \n");
    stdo("  terminate [PID] : kill process\n  lsps : list processes\n  mem : get memory usage\n  mount\n  dir : list files\n");
  }else if((args[0][0]=='.')&&(args[0][1]=='/')){
    exec_file(args[0]+2);
  }else{
    stde("Not a command:");
    stde(args[0]);
  }
  stdo("\n");
nonewline:
  return;
}
void k_init() {
  vga.begin(11,10);
  randomSeed(millis()+analogRead(A5));
  stdo=term_print;
  stde=term_error;
  stdo("Loading...\n");
  init_fs();
  if(mount()){
    stdo("Mounted SD card.\r");
  }else{
    stde("Failed to mount SD card.\r");
  }
  setup_keyboard();
  stdo("Loaded keyboard.\r");
  rows=256;//vga.y_tiles()*16;
  cols=18*16;//vga.x_tiles()*16;
  #ifdef USE_CYRILLIC
  alph_setcurs(0,0);
  #endif
  stdo("Entering user mode...\r");
}
#endif
