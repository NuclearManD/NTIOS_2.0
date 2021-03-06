#include "platform.h"
#include "driver_api.h"
#include <stdlib.h>

extern "C" void __cxa_pure_virtual() { while (1); }

void *operator new(size_t s) 
{ 
    return malloc(s); 
} 
  
void *operator new[](size_t s) 
{ 
    return malloc(s); 
} 
  
void operator delete(void *m) 
{ 
    free(m); 
} 
  
void operator delete[](void *m) 
{ 
    free(m); 
} 

int main(void){
	// initialization stuff goes here
	return entry();
}

void preinit_platform_drivers(){
	atmega328::uart.preinit();
	add_driver(&atmega328::uart);
	set_primary_terminal(&atmega328::uart);
	
	add_driver(&atmega328::gpio);
}
void init_platform_drivers(){
	
}
void postinit_platform_drivers(){
	
}


int freeRam() {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
