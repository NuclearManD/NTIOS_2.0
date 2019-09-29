#pragma GCC diagnostic warning "-fpermissive"
//#pragma GCC diagnostic warning "-pedantic"
#include "NTIKernel.h"
#define TERM_KBD_BUF 128
long timer;
void setup() {
  // put your setup code here, to run once:
  k_init();
  char term_cmd[64];
  //vga.set_cursor_pos(0, 0);
  //vga.clear();
  
  /*vga.set_color(1);
  vga.println("NTIOS");
  //vga.print(curdir);*/
  stdo("$ ");

  
  timer = millis();
}
char loop_term_cmd[TERM_KBD_BUF];
unsigned short loop_term_cnt = 0;
boolean curs_state = false; // false means cursur not showing, true means it is.
void loop() {
  if (Serial.available()){//kbd.available()) {
    /*if (curs_state)
      vga.print((char)8);*/
    char c = Serial.read();//kbd.read();
    if ((c == '\n') || (c == '\r')) {
      loop_term_cmd[loop_term_cnt] = 0;
      stdo("\n");
      system(loop_term_cmd);
      //vga.set_color(1);
      loop_term_cnt = 0;
      //vga.print(curdir);
      stdo("$ ");
    } else if (c == PS2_BACKSPACE) {
      if (loop_term_cnt > 0) {
        //vga.print(c);
        loop_term_cnt--;
      }
    } else {
      if (loop_term_cnt < TERM_KBD_BUF) {
        loop_term_cmd[loop_term_cnt] = c;
        loop_term_cnt++;
        //vga.print(c);
        Serial.print(c);
      }
    }
    //if (curs_state)
      //vga.print('_');
  }
  /*if (timer + 250 < millis()) {
    timer = millis();
    curs_state = !curs_state;
    if (curs_state)
      vga.print('_');
    else
      vga.print((char)8);
  }*/
}
