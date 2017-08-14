#pragma GCC diagnostic warning "-fpermissive"
//#pragma GCC diagnostic warning "-pedantic"
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h" // for attachInterrupt, FALLING
#else
#include "WProgram.h"
#endif
char* substr(char* arr, int begin, int len);
char* Nalloc(unsigned short length);
unsigned short len(char* d);
#define CPU_ATMEL_NTISYS

#define redraw __redraw[gr.cprocess]
#include <NMT_GFX.h>
#include <GEAR.h>
#include <PS2Keyboard.h>
#include "fs.h"
#include "uJ/common.h"
#include "uJ/uc_HD44780.h"
//#include "UJC.h"
int rows, cols;
#define system Nsystem
GearControl gr;
byte data = 0;
NMT_GFX vga;
PS2Keyboard kbd;
static volatile uint8_t *more_RAM = reinterpret_cast<volatile uint8_t*>(0x8000);
byte selected=0;
bool term_opn=false;
byte term_y, term_x=0;
byte gui=0;
byte sel_process=0;
bool* __redraw;
void (*reset)()=0;

#include "Cyrillic.h"//  include here for dependencies

void term_close(){
  term_opn=false;
  term_y=0;
}
int freeRam() {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
char* substr(char* arr, int begin, int len)
{
    char* res = Nalloc(len+1);
    for (int i = 0; i < len; i++)
        res[i] = *(arr + begin + i);
    res[len] = 0;
    return res;
}
unsigned short len(char* d){
  unsigned short i=0;
  while(d[i]!=0)
    i++;
  return i;
}
unsigned short our_heap=0x8000;
unsigned short* dev2mem=(unsigned short*)0x8000;
unsigned short our_stack=0x7FFF;
char* Nalloc(unsigned short length){
  unsigned short tmp=our_heap;
  our_heap+=length;
  our_stack-=2;
  dev2mem[our_stack]=tmp;
  return (char*)tmp;
}
void Ndealloc(){
  if(our_stack>=0x7FFE){
    our_heap=0x8000;
    return;
  }
  our_heap=dev2mem[our_stack];
  our_stack+=2;
}
int Nfree(){
  return our_stack-(our_heap-0x8000)+1;
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
int Java(int argc, char** argv);
char* read(int* size, char* name){
  File f=SD.open(name);
  if(f){
    size[0]=f.size();
    char* ptr=Nalloc(size[0]);
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
  vga.print(q);
}
void print(char q){
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
void noprnt(char* x){}
void (*stdo)(char*)=noprnt;
void (*stde)(char*)=noprnt;
bool term_force=false;
void Nsystem(char* inp){
  char* args[10];
  byte cnt=1;
  char* src=Nalloc(len(inp)+1);
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
  }else if(!strcmp(args[0],"cls")){
    vga.set_cursor_pos(0,0);
    vga.clear();
    return; // escape newline
  }else if(!strcmp(args[0],"lsdev")){
    // list devices
    stdo(" 0 PS2 Keyboard\n 1 ");
    stdo(vga.get_card_ver());
    stdo("\n 2 RAM_32K");
    stdo("\n 3 SD card");
  }else if(!strcmp(args[0],"mem")){
    stdo("RAM bytes free: ");
    stdo(String(freeRam()).c_str());
    stdo("\nDev2 bytes free: ");
    stdo(String(Nfree()).c_str());
  }else if(!strcmp(args[0],"do")){
    if(cnt<3){
      stde("Usage: do (dev id) (func) [args...]");
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
        if(!strcmp(args[2],"dealloc")){
          our_heap=0x8000;
          if(cnt>=4){
            our_heap-=to_int(args[1]);
          }
          stdo("Bytes free: ");
          stdo(String(Nfree()).c_str());
        }else
          stde("Function non existent.");
      }else if(dev==3){
        /*if(!strcmp(args[2],"mount")){
          if(mount()){
            
          }
        }else
          stde("Function non existent.");*/
      }
    }
  }else if(!strcmp(args[0],"java")){
    Java(cnt,args);
  }else if(!strcmp(args[0],"help")){
    stdo(" : ALL commands MUST be lowercase.\n* Commands: \n");
    stdo("  terminate [PID] : kill process\n  lsps : list processes\n  mem : get memory usage\n  mount\n  do [dev] [cmd] <more>\n  lsdev : device list\n  java <classes> : run Java apps");
  }else{
    stde("Not a command:");
    stde(args[0]);
  }
  stdo("\n");
  Ndealloc();
}
void k_init() {
  // init kernel
  bitSet(XMCRA, SRE);  // enable external(:P)memory
  bitSet(XMCRB, XMM0); // release unused pin PC7
  bitClear(XMCRA, SRW10);
  bitClear(XMCRA, SRW11);
  __redraw=(bool*)Nalloc(40);
  vga.begin();
  load_cyrillic_alphabet();
  kbd.begin(A15, 3);
  mount();
  rows=vga.y_tiles()*16;
  cols=vga.x_tiles()*16;
  alph_setcurs(0,0);
}
uint8_t ujReadClassByte(uint8_t* pgmloc, uint16_t offset){
  return pgmloc[offset];
}
bool java_inited=false;
int Java(int argc, char** argv){

  uint32_t threadH;
  bool done;
  bool remaining;
  uint8_t ret;
  struct UjClass* mainClass = NULL;
  int i;
  if(!java_inited){
    ret = ujInit(NULL);
    if(ret != UJ_ERR_NONE){
      stde("ujInit() fail\n");
    }else
      java_inited=true;
  }
  if(argc == 1){
    stde("%s: No classes given");
    stde(argv[0]);
    return -1;
  }
  
  //load provided classes now
  
  argc--;
  argv++;
  do{
    done = false;
    remaining = false;
    for(i = 0; i < argc; i++){
    
      if(argv[i]){
        remaining = true;
        FILE f = open(argv[i], "rb");
        if(!f){
          stde(" Failed to open file\n");
          return -3;
        }
        
        ret = ujLoadClass((UInt32)f, (i == 0) ? &mainClass : NULL);
        if(ret == UJ_ERR_NONE){       //success
        
          done = true;
          argv[i] = NULL;
        }
        else if(ret == UJ_ERR_DEPENDENCY_MISSING){  //fail: we'll try again later
        
          //nothing to do here  
        }
        else{
          
          stde( "Failed to load class %d: %d\n", i, ret);
          return -4;
        }
      }
    }
  }while(done);
  
  for(i = 0; i < argc; i++) if(argv[i]){
    
    stde( "Completely failed to load class %d (%s)\n", i, argv[i]);
    return -5;
  }
  
  ret = ujInitAllClasses();
  if(ret != UJ_ERR_NONE){
    stde( "ujInitAllClasses() fail\n");
    return -6;  
  }
  
  //now classes are loaded, time to call the entry point
  
  threadH = ujThreadCreate(0);
  if(!threadH){
    stde( "ujThreadCreate() fail\n");
    return -7;  
  }
  
  i = ujThreadGoto(threadH, mainClass, "main", "()V");
  if(i == UJ_ERR_METHOD_NONEXISTENT){
  
    stde( "Main method not found!\n");
    return -8; 
  }
  while(ujCanRun()){
    
    i = ujInstr();
    if(i != UJ_ERR_NONE){
    
      stde( "Ret %d @ instr right before 0x%08lX\n", i, ujThreadDbgGetPc(threadH));
      return -9;
    }
  }
  
  return 0;
}
