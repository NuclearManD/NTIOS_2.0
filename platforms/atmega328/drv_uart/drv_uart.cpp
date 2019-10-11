#include "driver_api.h"
#include <avr/io.h> // This contains the definitions of the terms used

namespace atmega328{

class HW_UART: public Terminal{
public:
	void write(char c){
		PORTB = c;
	}
	void stdo(char* d){
		for(int i=0;d[i];i++)write(d[i]);
	}

	void stde(char* d){
		stdo(d);
		/*printf("%s",d);
		fflush(stdout);*/
	}

	bool available(){
		/*struct timeval tv = { 0L, 0L };
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(0, &fds);
		return select(1, &fds, NULL, NULL, &tv);*/
		return false;
	}

	char read(){
		/*int r;
		unsigned char c;
		if ((r = ::read(0, &c, sizeof(c))) < 0) {
			return r;
		} else {
			write(8);
			return c;
		}*/
		return 0;
	}

	void preinit(){
		DDRB = 0xFF;
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
