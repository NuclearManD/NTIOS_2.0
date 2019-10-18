#include "driver_api.hpp"

#include "Arduino.h"

class Term: public Terminal{
public:
  void write(char c){
    Serial.write(c);
  }
  void stdo(char* d){
    Serial.print(d);
  }

  void stde(char* d){
    Serial.print(d);
  }

  bool available(){
    return Serial.available()>0;
  }

  char read(){
    return Serial.read();
  }
  
  char* get_path(){
    return (char*)"uart";
  }
private:
  char avail;
  bool has_byte;
};

Term term;
