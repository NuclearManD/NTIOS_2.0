
#include <SPI.h>
#include <SD.h>
//#include "ROM_fs.h"

bool sd_mounted=false;
bool mount(){
  if(sd_mounted)
    return true;
  pinMode(53, OUTPUT);
  sd_mounted=SD.begin(53);
  return sd_mounted;
}
char* curdir;
void init_fs(){
  curdir="/";
}
class Nfile{
  public:
    int make(char* p,byte access){
      path=p;
      acc=access;
      if((access&FILE_READ)&&(access&FILE_WRITE)){
        return -1; // only read or write, not both.
      }
      if(access&FILE_READ){
          // SD card
          if(sd_mounted){
            File f=SD.open(p,access);
            data=malloc(f.size()+1);
            uint16_t i=0;
            while(f.available()){
              data[i]=f.read();
              i++;
            }
            data[i]=0;
          }else{
            return -1;
          }
      }else if(access&FILE_WRITE){
        data=malloc(132);  //  132 = 128 bytes plus 2 byte length descriptor plus 2 byte allocation length
        data[0]=128; // allocation length
        data[1]=0;
      }
    }
    char* read(){
      
    }
    void write(char* x){
      
    }
    void close(){
      
    }
  private:
    byte acc;
    byte dev;
    char* path;
    char* data;
};
Nfile* open(char* name,byte access){
  char* path;
  byte dev;
  if(name[0]=='/'){
    path=name;
  }else{
    path=malloc(len(name)+len(curdir)+1);
    uint16_t i=0;
    uint16_t x=0;
    while(name){
      path[i]=name[0];
      name++;
      i++;
    }
    while(curdir[x]){
      path[i]=curdir[x];
      x++;
      i++;
    }
    path[i]=0;
  }
  if(!strcmp(substr(path,0,4),"/ROM")){
    dev=4;
    path+=4;
  }else if(!strcmp(substr(path,0,4),"/SD3")){
    dev=3;
    path+=4;
  }else
    return 0;
  Nfile* tmp = (Nfile*)malloc(sizeof(Nfile));
  tmp->make(path, access);
  return tmp;
}
