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
		}else if(pin<14){
			pin-=8;
			DDRB&=~(1<<pin);
			DDRB|=mode<<pin;
		}else if(pin<20){
			pin-=14;
			DDRC&=~(1<<pin);
			DDRC|=mode<<pin;
		}else{
			return ERROR_NO_HARDWARE;
		}
		return 0;
	}
	int set_pin(int pin, bool value){
		if(pin<2)
			return ERROR_NOT_SUPPORTED;
		if(pin<8){
			PORTD&=~(1<<pin);
			if(value)PORTD|=1<<pin;
		}else if(pin<14){
			pin-=8;
			PORTB&=~(1<<pin);
			if(value)PORTB|=1<<pin;
		}else if(pin<20){
			pin-=14;
			PORTC&=~(1<<pin);
			if(value)PORTC|=1<<pin;
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
		}else if(pin<14){
			pin-=8;
			return (PINB>>pin)&1;
		}else if(pin<20){
			pin-=14;
			return (PINC>>pin)&1;
		}
		return false;
	}
	int get_mode(int pin){
		if(pin<0)
			return 0;
		if(pin<8){
			return (DDRD>>pin)&1;
		}else if(pin<14){
			pin-=8;
			return (DDRB>>pin)&1;
		}else if(pin<20){
			pin-=14;
			return (DDRC>>pin)&1;
		}
		return 0;
	}
	
	char* get_path(){
		return (char*)"gpio";
	}
};
	
AVR_GPIO gpio;
};
