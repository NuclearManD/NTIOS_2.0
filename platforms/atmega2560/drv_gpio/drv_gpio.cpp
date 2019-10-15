#include "driver_api.h"
#include <avr/io.h> // This contains the definitions of the terms used

namespace atmega2560{

class AVR_GPIO: public GPIOPort{
	int get_size(){
		return 24;
	}
	int set_mode(int pin, int mode){
		if(pin<8){
			DDRF&=~(1<<pin);
			DDRF|=mode<<pin;
		}else if(pin<16){
			pin-=8;
			DDRK&=~(1<<pin);
			DDRK|=mode<<pin;
		}else if(pin<24){
			pin-=16;
			DDRH&=~(1<<pin);
			DDRH|=mode<<pin;
		}else{
			return ERROR_NO_HARDWARE;
		}
		return 0;
	}
	int set_pin(int pin, bool value){
		if(pin<8){
			PORTF&=~(1<<pin);
			if(value)PORTF|=1<<pin;
		}else if(pin<16){
			pin-=8;
			PORTK&=~(1<<pin);
			if(value)PORTK|=1<<pin;
		}else if(pin<24){
			pin-=16;
			PORTH&=~(1<<pin);
			if(value)PORTH|=1<<pin;
		}else{
			return ERROR_NO_HARDWARE;
		}
		return 0;
	}
	bool get_pin(int pin){
		if(pin<0)
			return 0;
		if(pin<8){
			return (PINF>>pin)&1;
		}else if(pin<16){
			pin-=8;
			return (PINK>>pin)&1;
		}else if(pin<24){
			pin-=16;
			return (PINH>>pin)&1;
		}
		return false;
	}
	int get_mode(int pin){
		if(pin<0)
			return 0;
		if(pin<8){
			return (DDRF>>pin)&1;
		}else if(pin<16){
			pin-=8;
			return (DDRK>>pin)&1;
		}else if(pin<24){
			pin-=16;
			return (DDRH>>pin)&1;
		}
		return 0;
	}
	
	char* get_path(){
		return (char*)"gpio";
	}
};
	
AVR_GPIO gpio;
};
