#ifndef KERNEL_FUNCTIONS_H
#define KERNEL_FUNCTIONS_H

extern void stdo(char* d);
extern void stde(char* d);
extern void stdo(const char* d);
extern void stde(const char* d);
extern char* int_to_str(int i);
extern int freeRam();
extern unsigned short len(char* d);
extern int to_int(char* str);
extern char read();
extern bool available();
extern void __empty();
extern void system(char* inp);
extern char* fs_resolve(char* fs_buffer, char* loc);
extern bool dircmp(char* a, char* b);
extern "C" char* itoa(int value, char* result, int base);


#endif
