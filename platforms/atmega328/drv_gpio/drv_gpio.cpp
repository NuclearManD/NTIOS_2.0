#include "driver_api.h"
#include <avr/io.h> // This contains the definitions of the terms used

namespace atmega328{

class AVR_GPIO: public GPIOPort{
	int get_size(){
		return 20;
	}
	int set_mode(int pin, int mode){
		if(pin<2)
			return ERROR_NOT_SUPPORTED;
		if(pin<8){
			DDRD&=~(1<<pin);
			DDRD|=mode<<pin;
		}else if(pin<13){
			DDRB&=~(1<<pin);
			DDRB|=mode<<pin;
		}else if(pin<20){
			DDRC&=~(1<<pin);
			DDRC|=mode<<pin;
		}else{
			return ERROR_NO_HARDWARE;
		}
		return 0;
	}
	int set_pin(int pin, bool value){
		char v = value ? 1 : 0;
		if(pin<2)
			return ERROR_NOT_SUPPORTED;
		if(pin<8){
			PORTD&=~(1<<pin);
			DDRD|=v<<pin;
		}else if(pin<13){
			DDRB&=~(1<<pin);
			DDRB|=v<<pin;
		}else if(pin<20){
			DDRC&=~(1<<pin);
			DDRC|=v<<pin;
		}else{
			return ERROR_NO_HARDWARE;
		}
		return 0;
	}
	bool get_pin(int pin){
		if(pin<0)
			return 0;
		if(pin<8){
			return (PIND>>pin)&1;
		}else if(pin<13){
			return (PINB>>pin)&1;
		}else if(pin<20){
			return (PINC>>pin)&1;
		}
		return false;
	}
	int get_mode(int pin){
		if(pin<0)
			return 0;
		if(pin<8){
			return (PIND>>pin)&1;
		}else if(pin<13){
			return (PINB>>pin)&1;
		}else if(pin<20){
			return (PINC>>pin)&1;
		}
		return 0;
	}
	
	char* get_path(){
		return (char*)"gpio";
	}
};
	
AVR_GPIO gpio;
};
