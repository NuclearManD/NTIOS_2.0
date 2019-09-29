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
  if (available()){
    char c = read();
    if ((c == '\n') || (c == '\r')) {
      loop_term_cmd[loop_term_cnt] = 0;
      stdo("\n");
      system(loop_term_cmd);
      loop_term_cnt = 0;
      stdo("$ ");
    } else if (c == CHAR_BACKSPACE) {
      if (loop_term_cnt > 0) {
        loop_term_cnt--;
        char ch[] = {c, 0};
        stdo(ch);
      }
    } else {
      if (loop_term_cnt < TERM_KBD_BUF) {
        loop_term_cmd[loop_term_cnt] = c;
        loop_term_cnt++;
        char ch[] = {c, 0};
        stdo(ch);
      }
    }
  }
}
