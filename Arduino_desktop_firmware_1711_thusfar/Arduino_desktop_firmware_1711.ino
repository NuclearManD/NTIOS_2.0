#include <PS2Keyboard.h>
#include <NMT_GFX.h>
#include "Icons.h"
NMT_GFX ngt;
#include "basic.h"
#include <GEAR.h>
GearControl gr;
char* pgm="var 6=\"lel\"PRINT tostr \"Khalo le monden!\"PRINT 6";
byte compiled[100];
int compiled_len=0;
PS2Keyboard kbd;
void setup() {
  Serial.begin(9600);
  kbd.begin(22,21);
  ngt.begin();
  compiled_len=compile(pgm,compiled);
  for(byte i=0;i<compiled_len;i++){
    Serial.print(compiled[i],HEX);
    Serial.print(' ');
    if((i+1)%16==0)
      Serial.println();
  }
  ngt.println("Please wait...");
  setup_basic(print_func);
  executeCompiledCode(compiled, compiled_len);
  ngt.print("> ");
  
  //ngt.println("Booting up...");
}
void print_func(char* c){
  ngt.println(c);
}
char lgt[200];
int idx=0;
void loop() {
  if(kbd.available()){
    char c=kbd.read();
    ngt.print(c);
    if(c=='\r'){
      lgt[idx]=0;
      idx=0;
      compiled_len=compile(lgt,compiled);
      Serial.println('\n');
      for(byte i=0;i<compiled_len;i++){
        Serial.print(compiled[i],HEX);
        Serial.print(' ');
        if((i+1)%16==0)
          Serial.println();
      }
      executeCompiledCode(compiled, compiled_len);
      
      ngt.print("> ");
    }else if(c==8){//BKSPS
      if(idx>0)
        idx--;
      else
        ngt.print(' ');
    }else{
      lgt[idx]=c;
      idx++;
    }
  }
  
  //gr.run();
}
void spawn(void (*task)(void),char* name){
  gr.addProcess(task,__empty,name,P_KILLABLE);
}

