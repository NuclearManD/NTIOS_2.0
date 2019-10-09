#ifndef NTI_KERNEL_H
#define NTI_KERNEL_H
#pragma GCC diagnostic warning "-fpermissive"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h" // for attachInterrupt, FALLING
#else
#include "WProgram.h"
#endif

#include "programs/program.h"
#include "drivers/drivers.h"

/*
 * Some quick fixes to be handled later - just to get it to compile.
 */

bool sd_mounted = false;

char* substr(char* arr, int begin, int len);
void Nsystem(char* inp);
unsigned short len(char* d);
#define CPU_ATMEL_NTISYS

#include <GEAR.h>
#include <PS2Keyboard.h>

GearControl gr;
byte data = 0;
PS2Keyboard kbd;

void (*reset)()=0;

Terminal* primary_term = new VoidTerminal();
FileSystem* root_fs;

void set_primary_terminal(Terminal* term){
  primary_term = term;
}

void set_root_fs(FileSystem* fs){
  root_fs = fs;
}

void stdo(char* d){
  primary_term->stdo(d);
}
void stde(char* d){
  primary_term->stde(d);
}
char read(){
  return primary_term->read();
}
bool available(){
  return primary_term->available();
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

int launch(void (*a)(),void (*b)(),char* name="?", void (*c)()=__empty){
  return gr.addProcess(a,b,name,c,P_KILLER|P_KILLABLE);  // do this before addProcess() to get ID of next new process
}

void gear_stopwait(){
  for(byte i=0;i<gr.processes;i++){
    gr.ftimes[i]=millis()+gr.fupd_rate;
  }
}

char curdir[128];
char* fs_resolve(char* fs_buffer, char* loc){
  char tmp[32];
  int index=0;
  int copied=0;
  int last_index=0;
  if(loc[0]!='/'){
    for(int i=0;i<=strlen(curdir);i++){
      if(curdir[i]=='/'||curdir[i]==0){
        if(!strcmp(tmp,".")){
          ;
        }else if(!strcmp(tmp,"..")){
          index=last_index;
        }else{
          last_index=index;
          for(int j=0;j<copied;j++){
            fs_buffer[index]=tmp[j];
            index++;
          }
          if(fs_buffer[index-1]!='/'){
            fs_buffer[index]='/';
            index++;
          }
        }
        copied=0;
      }else{
        tmp[copied]=curdir[i];
        copied++;
      }
    }
    copied=0;
  }
  for(int i=0;i<=strlen(loc);i++){
    if(loc[i]=='/'||loc[i]==0){
      if(!strcmp(tmp,".")){
        ;
      }else if(!strcmp(tmp,"..")){
        index=last_index;
      }else{
        last_index=index;
        for(int j=0;j<copied;j++){
          fs_buffer[index]=tmp[j];
          index++;
        }
        if(fs_buffer[index-1]!='/'){
          fs_buffer[index]='/';
          index++;
        }
      }
      copied=0;
    }else{
      tmp[copied]=loc[i];
      copied++;
    }
  }
  if(loc[strlen(loc)-1]=='/'){
    if(fs_buffer[index-1]!='/')
      fs_buffer[index]='/';
    fs_buffer[index+1]=0;
  }else if(fs_buffer[index-1]=='/'){
    fs_buffer[index-1]=0;
  }else
    fs_buffer[index]=0;
  return fs_buffer;
}

bool dircmp(char* a, char* b){
  char bufa[len(a)+16];
  char bufb[len(b)+16];
  fs_resolve(bufa, a);
  fs_resolve(bufb, b);
  
}

bool exists(char* path){
  char buffer[len(path)+16];
  return root_fs->exists(fs_resolve(buffer, path));
}
bool isfile(char* path){
  char buffer[len(path)+16];
  return root_fs->isfile(fs_resolve(buffer, path));
}
char* ls(char* path, int i){
  char buffer[len(path)+16];
  return root_fs->ls(fs_resolve(buffer, path), i);
}
int mkdir(char* path){
  char buffer[len(path)+16];
  return root_fs->mkdir(fs_resolve(buffer, path));
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
  if(!strcmp(args[0],"su")){
    gr.p_perms[gr.cprocess]=0xFF;
  }else if(!strcmp(args[0],"mem")){
    stdo("RAM bytes free: ");
    char buf[10];
    stdo(itoa(freeRam(), buf, 10));
  }else if(!strcmp(args[0],"ls")){
    char* path;
    if(cnt<2)
      path = curdir;
    else
      path = args[1];
    if(ls(path, 0)==0){
      stde("Not a directory: '");
      stde(path);
      stde("'");
    }else{
      int i = 1;
      while(true){
        char* fname = ls(path, i);
        if(fname==0)break;
        stdo(fname);
        stdo("\n");
        i++;
      }
    }
  }else if(!strcmp(args[0],"cd")){
    if(cnt<2){
      stde("Usage: cd [directory]");
    }else{
      if(exists(args[1])&&(!isfile(args[1]))){
        strcpy(curdir, args[1]);
      }else
        stde("Not a directory.");
    }
  }else if(!strcmp(args[0],"mkdir")){
    if(cnt<2)
      stde("Usage: mkdir [directory name]");
    else{
      int result = mkdir(args[1]);
      if(result!=0){
        stde(("Error "+String(result)+" in mkdir").c_str());
      }
    }
  }else if(!strcmp(args[0],"reboot")){
    asm volatile ("  jmp 0");  
  }else{
    // try program execution
    execute_program(args, cnt);
  }
  stdo("\n");
nonewline:
  return;
}
void k_init() {
  Serial.begin(115200);
  curdir[0] = '/';
  load_drivers();
  add_driver(new VoidTerminal());

  stdo("Running program setup...\n");
  init_programs();
  
  randomSeed(millis()+analogRead(A5));

  stdo("Entering user mode...\n\n");
}
#endif
