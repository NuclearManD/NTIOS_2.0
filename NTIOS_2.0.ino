#pragma GCC diagnostic warning "-fpermissive"

#include "NTIKernel.h"

#define TERM_KBD_BUF 128

void setup() {
  k_init();
  stdo("$ ");
}

char loop_term_cmd[TERM_KBD_BUF];
unsigned short loop_term_cnt = 0;
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
