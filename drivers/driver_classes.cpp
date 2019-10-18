#include "graphics_drivers.h"
#include "drivers.h"

/*
 * 
 * GRAPHICS HARDWARE
 * 
 */


int GraphicsHardware::tile_color(unsigned short a, unsigned char b){
	return ERROR_NOT_SUPPORTED;
}

void GraphicsHardware::print(char* x){
	int i=0;
	while(x[i]!=0){
		this->print(x[i]);
		i++;
	}
}
void GraphicsHardware::println(char* x){
	int i=0;
	while(x[i]!=0){
		this->print(x[i]);
		i++;
	}
	this->print('\n');
}
void GraphicsHardware::println(const char* x){
	this->println((char*)x);
}
void GraphicsHardware::print(const char* x){
	this->print((char*)x);
}


int GraphicsHardware::get_type(){
	return DRIVER_TYPE_GRAPHICS_HARDWARE;
}

char* GraphicsHardware::get_desc(){
	return (char*)"unknown";
}

/*
 * GRAPHICS DISPLAY
 * 
 */



void GraphicsDisplay::display_setup(GraphicsHardware* host, int stde_color, int stdo_color){
	this->host = host;
	display_id = drv_display_cnt;
	drv_display_cnt+=1;
	name[0]='m';
	name[1]='o';
	name[2]='n';
	name[3]='0'+(display_id/10);
	name[4]='0'+(display_id%10);
	name[5]=0;
	
	int color_type = host->get_color_type();
	
	if(stde_color==-1){
		switch(color_type){
			case COLOR_TYPE_BW:
				stde_color = 1;			// white
				break;
			case COLOR_TYPE_GRAY8:
				stde_color = 192;		// light gray
				break;
			case COLOR_TYPE_RGB8:
				stde_color = 0xE0;		// red
				break;
			case COLOR_TYPE_NES8:
			case COLOR_TYPE_NES16:
				stde_color = 2;			// color 2 (whichever it is)
				break;
			case COLOR_TYPE_GRAY16:
				stde_color = 0xD000;	// light gray
				break;
			case COLOR_TYPE_RGB16:
				stde_color = 0xFC00;	// red
				break;
		}
	}
	if(stdo_color==-1){
		switch(color_type){
			case COLOR_TYPE_BW:
				stdo_color = 1;			// white
				break;
			case COLOR_TYPE_GRAY8:
				stdo_color = 255;		// white
				break;
			case COLOR_TYPE_RGB8:
				stdo_color = 0xFF;		// white
				break;
			case COLOR_TYPE_NES8:
			case COLOR_TYPE_NES16:
				stdo_color = 1;			// color 1 (whichever it is)
				break;
			case COLOR_TYPE_GRAY16:
				stdo_color = 0xFFFF;	// white
				break;
			case COLOR_TYPE_RGB16:
				stdo_color = 0xFFFF;	// white
				break;
		}
	}
	stde_c = stde_color;
	stdo_c = stdo_color;
}
void GraphicsDisplay::stdo(char* d){
	host->set_color(stdo_c);
	host->print(d);
}
void GraphicsDisplay::stde(char* d){
	host->set_color(stde_c);
	host->print(d);
}
char GraphicsDisplay::read(){
	return -1;
}
bool GraphicsDisplay::available(){
	return false;
}
int GraphicsDisplay::get_type(){
	return DRIVER_TYPE_TERM;
}
void GraphicsDisplay::set_blinking(bool blink){
	
}
int GraphicsDisplay::load_font(unsigned char** font, int height, int length){
	return ERROR_NOT_SUPPORTED;
}
char* GraphicsDisplay::get_path(){
	return name;
}

/*
 * 
 * TERMINAL
 * 
 */


int Terminal::get_type(){
	return DRIVER_TYPE_TERM;
}
void Terminal::set_blinking(bool blink){}
int Terminal::set_font(unsigned char** font, int height, int length){
	return ERROR_NOT_SUPPORTED;
}

/*
 * 
 * KEYBOARD
 * 
 */


int Keyboard::get_type(){
	return DRIVER_TYPE_KEYBOARD;
}

/*
 * FILE HANDLE
 */

int FileHandle::write(char* str){
	return this->write(str, len(str));
}

/*
 * 
 * VOID TERMINAL
 * 
 */


char VoidTerminal::read(){
	return 0;
}
bool VoidTerminal::available(){
	return false;
}
char* VoidTerminal::get_path(){
	return (char*)"null";
}
void VoidTerminal::stdo(char* d){}
void VoidTerminal::stde(char* d){}

/*
 * 
 * GPIO PORT
 * 
 */

int GPIOPort::get_type(){
	return DRIVER_TYPE_GPIO;
}
