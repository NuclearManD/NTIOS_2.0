#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SERIAL_BUFFER_SIZE 64

class UART0_Term: public Terminal{
public:
	void stdo(char* d){
		Serial.print(d);
	}

	void stde(char* d){
		Serial.print(d);
	}

	bool available(){
		return Serial.available();
	}

	char read(){
		return Serial.read();
	}
	
	void setup_port(int baudrate){
		
		UBRRL = 
		UBRRH = 
	};

	void uart_preinit(){
		
		set_primary_terminal(this);
		g_stdo("UART set to primary terminal.\n");
	}
	
	char* get_path(){
		return "uart0";
	}
protected:
	int bytes_in_ready;
	char in_buffer[SERIAL_BUFFER_SIZE];
};

UART0_Term uart;
