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
	atmega2560::HW_UART* primary = new atmega2560::HW_UART(0,19200);
	add_driver(primary);
	add_driver(new atmega2560::HW_UART(1,19200));
	add_driver(new atmega2560::HW_UART(2,115200));
	add_driver(new atmega2560::HW_UART(3,115200));
	set_primary_terminal(primary);
	
	add_driver(&atmega2560::gpio);
}
void init_platform_drivers(){
	
}
void postinit_platform_drivers(){
	
}
