
#include <PS2Keyboard.h>
PS2Keyboard* kbd;

#define KBD_TYPE_HWS  0x01  // hardware serial
#define KBD_TYPE_PS2  0x02

byte kbd_types[]={KBD_TYPE_HWS};
long kbd_meta []={115200};

byte num_keyboards=1;

void err_mult_def(){
  stde("Error: Keyboard defined twice!\r > Ignoring...\r");
}


void setup_keyboard(){
  bool hws_done=false;
  bool ps2_done=false;
  for(int i=0;i<num_keyboards;i++){
    byte t=kbd_types[i];
    if(t==KBD_TYPE_HWS){
      if(hws_done){
        err_mult_def();
        continue;
      }
      hws_done=true;
      Serial.begin(kbd_meta[i]);
    }else if(t==KBD_TYPE_PS2){
      if(ps2_done){
        err_mult_def();
        continue;
      }
      ps2_done=true;
      kbd = new PS2Keyboard();
      kbd->begin((int)(kbd_meta[i]>>8),(int)(kbd_meta[i]&255));
    }
  }
}
int kbd_read(){
  bool hws_done=false;
  bool ps2_done=false;
  for(int i=0;i<num_keyboards;i++){
    byte t=kbd_types[i];
    if(t==KBD_TYPE_HWS){
      if(hws_done){
        continue;
      }
      hws_done=true;
      if(Serial.available())
        return Serial.read();
    }else if(t==KBD_TYPE_PS2){
      if(ps2_done){
        continue;
      }
      ps2_done=true;
      if(kbd->available())
        return kbd->read();
    }
  }
  return -1;
}
int kbd_available(){
  bool hws_done=false;
  bool ps2_done=false;
  int total=0;
  for(int i=0;i<num_keyboards;i++){
    byte t=kbd_types[i];
    if(t==KBD_TYPE_HWS){
      if(hws_done){
        continue;
      }
      hws_done=true;
      total+=Serial.available();
    }else if(t==KBD_TYPE_PS2){
      if(ps2_done){
        continue;
      }
      ps2_done=true;
      total+=kbd->available();
    }
  }
  return total;
}

