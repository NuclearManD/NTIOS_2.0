#pragma GCC diagnostic warning "-fpermissive"

#include "NTIKernel.h"

#define TERM_KBD_BUF 128

char loop_term_cmd[TERM_KBD_BUF];

unsigned short loop_term_cnt = 0;

int entry(void) {
	k_init();
	stdo(curdir);
	stdo("$ ");
	while(true){
		if (available()){
			char c = read();
			if ((c == '\n') || (c == '\r')) {
				loop_term_cmd[loop_term_cnt] = 0;
				stdo("\n");
				system(loop_term_cmd);
				loop_term_cnt = 0;
				stdo(curdir);
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
	return -1;  // something went wrong if we're here, return negative.
}
