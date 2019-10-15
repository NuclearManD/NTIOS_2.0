#ifndef NTI_KERNEL_H
#define NTI_KERNEL_H
//#pragma GCC diagnostic warning "-fpermissive"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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

unsigned char data = 0;

void (*reset)()=0;

VoidTerminal void_term;
Terminal* primary_term = &void_term;
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
void stdo(const char* d){
  primary_term->stdo((char*)d);
}
void stde(const char* d){
  primary_term->stde((char*)d);
}
char read(){
  return primary_term->read();
}
bool available(){
  return primary_term->available();
}

char* int_to_str(int i, char* o){
  const char* a="0123456789ABCDEF";
  o[0] = a[(i >> 12) & 0xF];
  o[1] = a[(i >> 8) & 0xF];
  o[2] = a[(i >> 4) & 0xF];
  o[3] = a[i & 0xF];
  o[4]=0;
  return o;
}
int freeRam() {
  /*extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
  */
  return -1;
}

unsigned short len(char* d){
  unsigned short i=0;
  while(d[i]!=0)
    i++;
  return i;
}
int to_int(char* str){
  int out=0;
  for(unsigned char i=0;i<len(str);i++){
    out+=pow(10,i)*(str[i]-'0');
  }
  return out;
}

char curdir[128];
char* fs_resolve(char* fs_buffer, char* loc);

bool dircmp(char* a, char* b);

bool exists(char* path);
bool isfile(char* path);
char* ls(char* path, int i);
int mkdir(char* path);

bool term_force=false;

char buf_0x10[256];

void system(char* inp){
  char* args[10];
  unsigned char cnt=1;
  char* src=buf_0x10;
  args[0]=src;
  
  for(unsigned short i=0; i<len(inp); i++){
    char c=inp[i];
    if(c!=' ')
      src[i]=c;
    else{
      src[i]=0;
      args[cnt]=i+1+src;
      
      cnt++;
      while(inp[i+1]==' ')
        i++;
    }
  }
  src[len(inp)]=0;
  if(!strcmp(args[0],"mem")){
    stdo("RAM unsigned chars free: ");
    char buf[10];
	snprintf(buf, 10,  "%i", freeRam());
    stdo(buf);
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
		char buf[10];
        stde("Error ");
		snprintf(buf, 10,  "%i", result);
		stde(buf);
		stde(" in mkdir");
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
  curdir[0] = '/';
  load_drivers();
  add_driver(new VoidTerminal());

  stdo("Running program setup...\n");
  init_programs();

  stdo("Entering user mode...\n\n");
}
#endif
