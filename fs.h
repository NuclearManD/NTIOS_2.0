
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
