#ifndef KERNEL_FUNCTIONS_H
#define KERNEL_FUNCTIONS_H

#include <NMT_GFX.h>

extern void stdo(char* d);
extern void stde(char* d);
extern char* int_to_str(int i);
extern int freeRam();
extern unsigned short len(char* d);
extern int to_int(char* str);
extern char read();
extern bool available();
extern void __empty();
extern int launch(void (*a)(),void (*b)(),char* name="?", void (*c)()=__empty);
extern void system(char* inp);

extern NMT_GFX vga;


#endif
