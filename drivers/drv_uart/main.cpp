
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h" // for attachInterrupt, FALLING
#else
#include "WProgram.h"
#endif

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

	void uart_preinit(){
		Serial.begin(115200);
		set_primary_terminal(this);
		g_stdo("UART set to primary terminal.\n");
	}

	void uart_init(){
	}
	
	char* get_path(){
		return "uart0";
	}
};

UART0_Term uart;
