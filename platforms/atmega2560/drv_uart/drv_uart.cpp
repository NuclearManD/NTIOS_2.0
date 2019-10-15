#include "driver_api.h"
#include <avr/io.h> // This contains the definitions of the terms used
#include <stdio.h>

namespace atmega2560{

class HW_UART: public Terminal{
public:
	HW_UART(int id, int baud){
		sprintf(path, "uart%i", id);
		idn = (char)id;
		
		unsigned long prescale = (((F_CPU / (baud * 16UL))) - 1);

		switch(id){
			case 0:
				UCSR0B |= (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry 
				UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes 
				// load prescale
				UBRR0H = (prescale >> 8);
				UBRR0L = prescale;
				break;
			case 1:
				UCSR1B |= (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry 
				UCSR1C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes 
				// load prescale
				UBRR1H = (prescale >> 8);
				UBRR1L = prescale;
				break;
			case 2:
				UCSR2B |= (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry 
				UCSR2C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes 
				// load prescale
				UBRR2H = (prescale >> 8);
				UBRR2L = prescale;
				break;
			case 3:
				UCSR3B |= (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry 
				UCSR3C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes 
				// load prescale
				UBRR3H = (prescale >> 8);
				UBRR3L = prescale;
				break;
		}
	}
	void write(char c){
		switch(idn){
			case 0:
				while ((UCSR0A & (1 << UDRE0)) == 0);
				UDR0 = c;
				break;
			case 1:
				while ((UCSR1A & (1 << UDRE1)) == 0);
				UDR1 = c;
				break;
			case 2:
				while ((UCSR2A & (1 << UDRE2)) == 0);
				UDR2 = c;
				break;
			case 3:
				while ((UCSR3A & (1 << UDRE3)) == 0);
				UDR3 = c;
				break;
			default:
				break;
		}
	}
	void stdo(char* d){
		for(int i=0;d[i];i++)write(d[i]);
	}

	void stde(char* d){
		stdo(d);
	}

	bool available(){
		switch(idn){
			case 0:
				return (UCSR0A & (1 << RXC0)) != 0;
			case 1:
				return (UCSR1A & (1 << RXC0)) != 0;
			case 2:
				return (UCSR2A & (1 << RXC0)) != 0;
			case 3:
				return (UCSR3A & (1 << RXC0)) != 0;
		}
		return false;
	}

	char read(){
		switch(idn){
			case 0:
				return UDR0;
			case 1:
				return UDR1;
			case 2:
				return UDR2;
			case 3:
				return UDR3;
		}
		return 0;
	}
	
	char* get_path(){
		return path;
	}
private:
	char avail;
	bool has_byte;
	char path[6];
	char idn;
};

}
