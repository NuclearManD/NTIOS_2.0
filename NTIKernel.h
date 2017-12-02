#pragma GCC diagnostic warning "-fpermissive"
//#pragma GCC diagnostic warning "-pedantic"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h" // for attachInterrupt, FALLING
#else
#include "WProgram.h"
#endif
#include "basic.h"
char* substr(char* arr, int begin, int len);
String term_curdir="/";
void Nsystem(char* inp,char* curdir=term_curdir.c_str());
unsigned short len(char* d);
#define CPU_ATMEL_NTISYS

#define redraw __redraw[gr.cprocess]
#include <NMT_GFX.h>
#include <GEAR.h>
#include <PS2Keyboard.h>
#include "fs.h"
int rows, cols;
#define system Nsystem
GearControl gr;
byte data = 0;
NMT_GFX vga;
PS2Keyboard kbd;
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
#ifdef USE_CYRILLIC
#include "Cyrillic.h"//  include here for dependencies
#endif
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
int exec_file(char* name){
  if(!sd_mounted){
    stde("No storage.");
    return 0;
  }
  char* data;
  char compiled[256];
  int length;
  File f=SD.open(name,FILE_READ);
  if(!strcmp(name+len(name)-3,"BIN")){
    length=f.size();
    byte i=0;
    while (f.available()) {
      compiled[i]=(f.read());
      i++;
    }
  }else{
    data=malloc(f.size()+1);
    byte i=0;
    while (f.available()) {
      data[i]=(f.read());
      i++;
    }
    data[i]=0;
    length=compile(data,compiled);
    free(data);
  }
  f.close();
  setup_basic(stdo);
  return executeCompiledCode(compiled, length);
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
void window(int a, int b, int c, int d){
  a=(a+1)*6-2;
  b=(b+1)*13-1;
  c=(c+1)*6+2;
  d=(d+1)*13+3;
  vga.set_color(1);
  vga.fill_box(a,b,c,d);
  vga.set_color(2);
  vga.box(a,b,c,d);
  vga.fill_box(a,b-5,c+1,b);
}
void gear_stopwait(){
  for(byte i=0;i<gr.processes;i++){
    gr.ftimes[i]=millis()+gr.fupd_rate;
  }
  for(byte i=0;i<40;i++)
    __redraw[i]=true;
}
void alert(const char* q){
  window(3,2,30,4);
  vga.set_color(2);
  vga.set_cursor_pos(3,2);
  vga.print(q);
  vga.set_cursor_pos(4,3);
  vga.set_color(3);
  vga.print("OK");
  vga.set_color(2);
  while(true){
    if(kbd.available())
      if(kbd.read()==PS2_ENTER)
        break;
  }
  vga.set_color(0);
  vga.fill_box(22,33,117,68);
  gear_stopwait();
}
bool okcancel(const char* q){
  window(3,2,40,4);
  vga.set_color(2);
  vga.set_cursor_pos(3,2);
  vga.print(q);
  vga.set_cursor_pos(4,3);
  vga.set_color(2);
  vga.print("OK");
  vga.set_color(3);
  vga.print(" CANCEL");
  vga.set_color(2);
  bool sel=false;
  while(true){
    if(kbd.available()){
    uint16_t c=kbd.read();
      if(c==PS2_ENTER)
        break;
      else if((c==PS2_RIGHTARROW)||(c==PS2_LEFTARROW)){
        sel=!sel;
        if(sel){
          vga.set_cursor_pos(4,3);
          vga.set_color(3);
          vga.print("OK");
          vga.set_color(2);
          vga.print(" CANCEL");
          vga.set_color(2);
        }else{
          vga.set_cursor_pos(4,3);
          vga.set_color(2);
          vga.print("OK");
          vga.set_color(3);
          vga.print(" CANCEL");
          vga.set_color(2);
        }
      }
    }
  }
  vga.set_color(0);
  vga.fill_box(22,33,117,68);
  gear_stopwait();
  return sel;
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
void println(const char* q){
  if(term_opn==false){
    window(0,0,30,12);
    for(int i=0;i<gr.processes;i++){
      __redraw[i]=true;
    }
  }
  term_opn=true;
  vga.set_cursor_pos(term_x,term_y);
  term_y++;
  term_x=0;
  for(byte i=0;i<len(q);i++){
    char c=q[i];
    if(c=='\n'||c=='\r')
      term_y++;
  }
  vga.set_color(2);
  vga.print(q);
}
void print(const char* q){
  if(term_opn==false){
    window(0,0,30,12);
    for(int i=0;i<gr.processes;i++){
      __redraw[i]=true;
    }
  }
  term_opn=true;
  vga.set_cursor_pos(term_x,term_y);
  for(byte i=0;i<len(q);i++){
    char c=q[i];
    if(c=='\n'||c=='\r'){
      term_y++;
      term_x=0;
    }else
      term_x++;
  }
  vga.set_color(2);
  vga.print(q);
}
void print(char q){
  vga.set_color(2);
  if(term_opn==false){
    window(0,0,30,12);
    for(int i=0;i<gr.processes;i++){
      __redraw[i]=true;
    }
  }
  term_opn=true;
  vga.set_cursor_pos(term_x,term_y);
  if(q!='\n' && q!='\r'){
    term_x++;
    if(q!=' ')
      vga.print(q);
  }else
    term_y++;
}
char* fileChooser(char* cd="/"){ // use char* for compatibility
  String curdir=cd;             // allocate on stack for best performance
  //char* last_working_dir=curdir.c_str();
  int sel=0; // 0=>textbox, 1+ => files & directories
  File dir;
  while(true){
    window(0,0,30,10);
    if(sel==0){
      vga.set_color(3);
    }else
      vga.set_color(2);
    vga.set_cursor_pos(1,1);
    vga.print(curdir.c_str());
    if(SD.exists(curdir.c_str()))
      dir = SD.open(curdir.c_str());
    //if(!SD.exists(curdir.c_str())){//!dir){
    //  dir = SD.open(last_working_dir);
    //}else
    //  dir = SD.open(curdir.c_str());//last_working_dir=curdir.c_str();
    if(SD.exists(curdir.c_str())||curdir.equals("/")){
      dir = SD.open(curdir.c_str());
      for(byte i=1;i<9;i++) {
        vga.set_cursor_pos(1,i+1);
        if(i==sel){
          vga.set_color(3);
        }else
          vga.set_color(2);
        File entry =  dir.openNextFile();
        if (! entry) {
          break;
        }
        vga.print(entry.name());
        if (entry.isDirectory()) {
          vga.print('/');
        } else {
          // files have sizes, directories do not
          for(byte j=0;j<16-len(entry.name());j++)
            vga.print(' ');
          vga.print("0x");
          vga.print(int_to_str(entry.size()));
          vga.print("\n");
        }
        entry.close();
      }
    }
    while(!kbd.available());
    uint16_t c=kbd.read();
    if(c==PS2_DOWNARROW)
      sel++;
    else if(c==PS2_UPARROW)
      sel--;
    else if(c==PS2_ESC)
      break;
    else if(sel==0){
      if(c==PS2_ENTER){
        if(SD.exists(curdir.c_str()))
          break;
        else
          sel=8;
      }else if(c==8){
        curdir=curdir.substring(0,curdir.length()-1);
      }else
        curdir+=(char)c;
    }else{
      if(c==PS2_ENTER){
        int i=2;
        dir = SD.open(curdir.c_str());
        File entry=dir.openNextFile();
        for(i;i<=sel;i++) {
          entry.close();
          entry = dir.openNextFile();
          if(!entry)
            break;
        }
        if(!curdir.endsWith("/"))
          curdir+='/';
        curdir+=entry.name();
        if (entry.isDirectory()) {
          curdir+='/';
        }
        entry.close();
        sel=0;
      }
    }
    sel=sel%8;
  }
  vga.set_color(0);
  vga.fill_box(22,33,117,68);
  gear_stopwait();
  return curdir.c_str();
}
void shell_upd();
void shell_fup();
boolean x_server_running=false;
void X_SERVER(){
  x_server_running=true;
  void (*stdo_tmp)(const char*)=stdo;
  void (*stde_tmp)(const char*)=stde;
  stdo=(void (*)(const char*))noprnt;
  stde=(void (*)(const char*))noprnt;
  stdo("Starting GUI...\n");
  __redraw[gr.addProcess(shell_upd,shell_fup,(char*)"Shell",__empty,P_ROOT|P_KILLER)]=true;
  vga.clear();

  // set color scheme
  
  vga.block_color(0x01,0);
  vga.block_color(0x41,0b00111111);
  vga.block_color(0x81,0b00000011);
  vga.block_color(0xC1,0b00011000);
  int quepie=vga.x_tiles()*vga.y_tiles();
  for(int i=0;i<quepie;i++){
    vga.tile_color(i,1);
  }
  
  for(byte i=0;i<gr.processes;i++){
    gr.ftimes[i]=millis()+gr.fupd_rate;
  }
  while(x_server_running){
    gr.run();
    if(gr.processes==0){
      alert("No more processes!");
      break;
    }
    if(kbd.available()){
      last_key=kbd.read();
      randomSeed(millis()*last_key);
    }else
      last_key=0;
    if(sel_process>=gr.processes){
      sel_process=0;
      sw_gui(0);
    }
  }
  for(int i=0;i<quepie;i++){
    vga.tile_color(i,0);
  }
  vga.clear();
  stdo=stdo_tmp;
  stde=stde_tmp;
  stde("GUI terminated.\n");
}
bool term_force=false;
void Nsystem(char* inp,char* curdir=term_curdir.c_str()){
  char* args[10];
  byte cnt=1;
  char* src=(char*)malloc(len(inp)+1);
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
    kbd.begin(22, 21);
  }else if(!strcmp(args[0],"cls")){
    vga.set_cursor_pos(0,0);
    vga.clear();
    return; // escape newline
  }else if(!strcmp(args[0],"lsdev")){
    // list devices
    stdo(" 0 PS2 Keyboard\n 1 ");
    stdo(vga.get_card_ver());
    //stdo("\n 2 RAM_32K");
    stdo("\n 3 SD card");
  }else if(!strcmp(args[0],"mem")){
    stdo("RAM bytes free: ");
    stdo(String(freeRam()).c_str());
  }else if(!strcmp(args[0],"do")){
    if(!(term_force||(gr.p_perms[gr.cprocess]&P_ROOT)==P_ROOT)){//cnt<3){
      stde("Root privladges required.");//"Usage: do (dev id) (func) [args...]");
    }else{
      byte dev=to_int(args[1]);
      if(dev==0)
        stde("This device hasn't any functions.");
      else if(dev==1){
        if(!strcmp(args[2],"cls"))
          vga.clear();
        else if(!strcmp(args[2],"reset"))
          stde("Not yet implimented.");
        else
          stde("Function non existent.");
      }else if(dev==2){
        if(!strcmp(args[2],"reset")){
        }else
          stde("Function non existent.");
      }else if(dev==3){
        if(!strcmp(args[2],"mount")){
          if(mount()){
            
          }
        }else
          stde("Function non existent.");
      }
    }
  }else if(!strcmp(args[0],"dir")){
    if(!sd_mounted){
      stde("No SD card mounted.");
    }else{
      File dir = SD.open(curdir);
      while (true) {
        File entry =  dir.openNextFile();
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
    }
  }else if(!strcmp(args[0],"cd")){
    if(cnt<2){
      stde("Usage: cd directory");
    }else{
      if(args[1][0]=='/'){
        File f=SD.open(args[1]);
        if(f&&f.isDirectory()){
          term_curdir=args[1];
          goto nonewline;
        }else
          stde("Not a directory.");
        f.close();
      }else{
        File f=SD.open((term_curdir+args[1]).c_str());
        if(f&&f.isDirectory()){
          term_curdir+=args[1];
          goto nonewline;
        }else{
          stde("Not a directory: ");
          stde((term_curdir+args[1]).c_str());
        }
        f.close();
      }
      if(!term_curdir.endsWith("/"))
        term_curdir+='/';
    }
  }else if(!strcmp(args[0],"logout")){
    x_server_running=false;
    stdo("Closing GUI...");
    for(byte i=0;i<gr.processes;i++){
      gr.__A_KILL(i);
    }
    gr.p_perms[39]=0xFF;
  }else if(!strcmp(args[0],"startx")){
    X_SERVER();
  }else if(!strcmp(args[0],"help")){
    stdo(" : ALL commands MUST be lowercase.\n* Commands: \n");
    stdo("  terminate [PID] : kill process\n  lsps : list processes\n  mem : get memory usage\n  mount\n  do [dev] [cmd] <more>\n  lsdev : device list\n  dir : list files");
  }else if((args[0][0]=='.')&&(args[0][1]=='/')){
    exec_file(args[0]+2);
  }else{
    stde("Not a command:");
    stde(args[0]);
  }
  stdo("\n");
nonewline:
  free(src);
}
void k_init() {
  vga.begin();
  randomSeed(millis()+analogRead(A5));
  stdo=term_print;
  stde=term_error;
  stdo("Loading...\n");
  if(mount())
    stdo("Mounted SD card.\r");
  else
    stde("Failed to mount SD card.\r");
  kbd.begin(22, 21);
  stdo("Loaded keyboard.\r");
  rows=vga.y_tiles()*16;
  cols=vga.x_tiles()*16;
  #ifdef USE_CYRILLIC
  alph_setcurs(0,0);
  #endif
  stdo("Entering user mode...\r");
}
