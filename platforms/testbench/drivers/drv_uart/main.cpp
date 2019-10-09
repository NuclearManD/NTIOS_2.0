#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "avr_uart/uart.h"
#include "avr_uart/uart.c"

#define UART_BAUDRATE 115200

class UART0_Term: public Terminal{
public:
	void write(char c){
		uart_putc(c);
	}
	void stdo(char* d){
		uart_puts(d);
	}

	void stde(char* d){
		uart_puts(d);
	}

	bool available(){
		if(has_byte)return true;
		unsigned int res = uart_getc();
		if(res&UART_NO_DATA)return false;
		avail = (char)res;
		has_byte = true;
		return true;
	}

	char read(){
		if(has_byte)return avail;
		return 0;
	}
	
	void setup_port(int baudrate){
		uart_init(UART_BAUD_SELECT(baudrate,F_CPU));
		has_byte = false;
	};

	void uart_preinit(){
		
		set_primary_terminal(this);
		g_stdo("UART set to primary terminal.\n");
	}
	
	char* get_path(){
		return "uart0";
	}
private:
	char avail;
	bool has_byte;
};

UART0_Term uart;
