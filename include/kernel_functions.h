#ifndef KERNEL_FUNCTIONS_H
#define KERNEL_FUNCTIONS_H

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
extern char* fs_resolve(char* fs_buffer, char* loc);
extern bool dircmp(char* a, char* b);

#ifdef __AVRASM_VERSION__
// AVR compiler does NOT have new and delete operators.

void* operator new(size_t objsize) { 
    return malloc(objsize); 
} 

void operator delete(void* obj) { 
    free(obj); 
}
#endif


#endif
