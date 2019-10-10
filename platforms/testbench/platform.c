#include "platform.h"
#include "driver_api.h"

int main(void){
	// initialization stuff goes here
	return entry();
}

void preinit_platform_drivers(){
	add_driver(&term);
	set_primary_terminal(&term);
}
void init_platform_drivers(){
	
}
void postinit_platform_drivers(){
	
}
