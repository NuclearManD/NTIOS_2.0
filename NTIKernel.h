#ifndef NTI_KERNEL_H
#define NTI_KERNEL_H
#pragma GCC diagnostic warning "-fpermissive"
//#pragma GCC diagnostic warning "-pedantic"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h" // for attachInterrupt, FALLING
#else
#include "WProgram.h"
#endif

#include "programs/program.h"

/*
 * Some quick fixes to be handled later - just to get it to compile.
 */

bool sd_mounted = false;

char* substr(char* arr, int begin, int len);
void Nsystem(char* inp);
unsigned short len(char* d);
#define CPU_ATMEL_NTISYS

#include <NMT_GFX.h>
#include <GEAR.h>
#include <PS2Keyboard.h>
int rows, cols;
GearControl gr;
byte data = 0;
NMT_GFX vga;
PS2Keyboard kbd;
byte selected=0;
bool term_opn=false;
byte term_y, term_x=0;
byte sel_process=0;

void (*reset)()=0;
void noprnt(char* x){}
void (*stdo)(char*)=noprnt;
void (*stde)(char*)=noprnt;

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

void ser_print(char* d){
  Serial.print(d);
}

char* int_to_str(int i){
  char* o=malloc(5);
  char* a="0123456789ABCDEF";
  o[0] = a[(i >> 12) & 0xF];
  o[1] = a[(i >> 8) & 0xF];
  o[2] = a[(i >> 4) & 0xF];
  o[3] = a[i & 0xF];
  o[4]=0;
  return o;
}
int freeRam() {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

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
  sel_process=gr.addProcess(a,b,name,c,P_KILLER|P_KILLABLE);  // do this before addProcess() to get ID of next new process
  return sel_process;
}

void gear_stopwait(){
  for(byte i=0;i<gr.processes;i++){
    gr.ftimes[i]=millis()+gr.fupd_rate;
  }
}

void shell_upd();
void shell_fup();
bool term_force=false;

char buf_0x10[256];

void system(char* inp){
  char* args[10];
  byte cnt=1;
  char* src=buf_0x10;
  args[0]=src;
  
  #ifdef UART_DEBUG
    Serial.print("Executing command sequence [");
  #endif
  
  for(unsigned short i=0; i<len(inp); i++){
    char c=inp[i];
    if(c!=' ')
      src[i]=c;
    else{
      src[i]=0;
      args[cnt]=(char*)(i+1+(unsigned short)src);
      
      #ifdef UART_DEBUG
        Serial.print(args[cnt]);
        Serial.print(" ");
      #endif
      
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
    /*if(mount())
      stdo("Success.");
    else
      stde("Unknown Error.");
    kbd.begin(4, 2);*/
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
      /*Serial.print("Opening directory ");
      Serial.println(curdir);
      File dir = SD.open(curdir);
      Serial.println("Rewinding directory...");
      dir.rewindDirectory();
      while (true) {
        Serial.println("Opening next file...");
        File entry =  dir.openNextFile();
        Serial.print("Opened ");
        Serial.println(entry.name());
        if (! entry) {
          break;
        }
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
      Serial.println("Command complete.");*/
    }
  }else if(!strcmp(args[0],"cd")){
    if(cnt<2){
      stde("Usage: cd directory");
    }else{
      /*Serial.print("Checking directory ");
      Serial.println(fs_resolve(args[1]));
      File f=SD.open(fs_resolve(args[1]));
      if(f&&f.isDirectory()){
        strcpy(curdir,fs_resolve(args[1]));
        Serial.println("Valid.");
        f.close();
        goto nonewline;
      }
      stde("Not a directory: ");
      stde(fs_resolve(args[1]));
      Serial.println("Invalid.  Closing...");
      f.close();*/
    }
  }else if(!strcmp(args[0],"mkdir")){
    if(cnt<2)
      stde("Usage: mkdir [directory name]");
    else{
      /*stdo("creating directory ");
      stdo(fs_resolve(args[1]));
      stdo("...\r");
      if(!mkdir(args[1])){
        stde("Error creating ");
        stde(fs_resolve(args[1]));
      }*/
    }
  }else if(!strcmp(args[0],"reboot")){
    asm volatile ("  jmp 0");  
  }else if(!strcmp(args[0],"help")){
    stdo(" : ALL commands MUST be lowercase.\n* Commands: \n");
    stdo("  terminate [PID] : kill process\n  lsps : list processes\n  mem : get memory usage\n  mount\n  dir : list files\n");
  }/*else if((args[0][0]=='.')&&(args[0][1]=='/')){
    exec_file(args[0]+2);
  }*/else{
    // try program execution
    execute_program(args, cnt);
  }
  stdo("\n");
nonewline:
  free(src);
}
void k_init() {
  #ifdef UART_DEBUG
    Serial.begin(9600);
    Serial.println("Debugging on this port.");
  #endif

  Serial.begin(9600);
  
  
  //vga.begin(11,10);
  randomSeed(millis()+analogRead(A5));
  stdo=ser_print;
  stde=ser_print;
  stdo("Loading...\n");
  /*init_fs();
  if(mount()){
    stdo("Mounted SD card.\r");
    Serial.println("SD card mounted.");
  }else{
    stde("Failed to mount SD card.\r");
    Serial.println("SD card failed to mount.");
  }*/
  //kbd.begin(4, 2);
  //stdo("Loaded keyboard.\r");
  rows=256;//vga.y_tiles()*16;
  cols=18*16;//vga.x_tiles()*16;

  stdo("Entering user mode...\n");
  
  #ifdef UART_DEBUG
    Serial.println("Entering user mode...");
  #endif
}
#endif
