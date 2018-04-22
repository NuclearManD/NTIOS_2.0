#ifndef SDFS_H
#define SDFS_H
#include <SPI.h>
#include <SD.h>
//#include <EEPROM.h>
//#include "ROM_fs.h"

bool sd_mounted=false;
bool mount(){
  if(sd_mounted)
    return true;
  pinMode(53, OUTPUT);
  pinMode(5, OUTPUT);
  sd_mounted=SD.begin(5);
  return sd_mounted;
}
char curdir[256];
void init_fs(){
  curdir[0]='/';
  curdir[1]=0;
}
char fs_buffer[256];
char* fs_resolve(char* loc){
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
bool mkdir(char* name){
  return SD.mkdir((const char *)fs_resolve(name));
}
#endif
