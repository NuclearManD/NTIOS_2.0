#include "platform.h"
#include "driver_api.h"

int main(void){
	// initialization stuff goes here
	return entry();
}

void preinit_platform_drivers(){
	atmega328::uart.preinit();
	add_driver(&atmega328::uart);
	set_primary_terminal(&atmega328::uart);
}
void init_platform_drivers(){
	
}
void postinit_platform_drivers(){
	
}
