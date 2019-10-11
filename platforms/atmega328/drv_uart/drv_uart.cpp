#include "driver_api.h"
#include <avr/io.h> // This contains the definitions of the terms used

#define USART_BAUDRATE 19200 
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

namespace atmega328{

class HW_UART: public Terminal{
public:
	void write(char c){
		while ((UCSR0A & (1 << UDRE0)) == 0);
		UDR0 = c;
	}
	void stdo(char* d){
		for(int i=0;d[i];i++)write(d[i]);
	}

	void stde(char* d){
		stdo(d);
	}

	bool available(){
		return (UCSR0A & (1 << RXC0)) != 0;
	}

	char read(){
		return UDR0;
	}

	void preinit(){
		UCSR0B |= (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry 
		UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes 

		UBRR0H = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value into the high byte of the UBRR register 
		UBRR0L = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register 
	}
	
	char* get_path(){
		return (char*)"uart";
	}
private:
	char avail;
	bool has_byte;
};

HW_UART uart;

}
