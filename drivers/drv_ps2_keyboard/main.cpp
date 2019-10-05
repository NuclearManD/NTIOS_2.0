
#include "PS2Keyboard.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h" // for attachInterrupt, FALLING
#else
#include "WProgram.h"
#endif

class PS2_Keyboard: public Keyboard{
public:
	bool available(){
		return kbd.available();
	}

	int read(){
		return kbd.read();
	}

	void kbd_preinit(){
		kbd.begin(4, 2);
	}
	
	char* get_path(){
		return "ps2_kbd";
	}
private:
	PS2Keyboard kbd;
};

PS2_Keyboard ps2_kbd;
