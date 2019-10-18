#include "ntikernel.hpp"
#include "driver_api.hpp"
#include "term.hpp"

void preinit_platform_drivers(){
  Serial.begin(115200);
  add_driver(&term);
  set_primary_terminal(&term);
}
void init_platform_drivers(){
  
}
void postinit_platform_drivers(){
  
}

int arduino_exec_pgm(char** argv, int argc){
  stde("Not a command: ");
  stde(argv[0]);
  return -1000;
}

int freeRam() {
  return 512*1024L*1024L; // Assume that we have plenty of free RAM
}

void setup(){
  int exit_status = entry();
}

void loop(){
  // code here should never be reached
}
