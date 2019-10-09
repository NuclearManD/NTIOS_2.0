#ifndef DRIVERS_H
#define DRIVERS_H

#define DRIVER_TYPE_TERM 0
#define DRIVER_TYPE_FS 1
#define DRIVER_TYPE_GRAPHICS_HARDWARE 2
#define DRIVER_TYPE_KEYBOARD 3

#define NOT_ERROR 0
#define ERROR_NOT_SUPPORTED -1
#define ERROR_NO_HARDWARE -2
#define ERROR_ALREADY_STARTED -3
#define ERROR_NOT_REMOVABLE -4
#define ERROR_NOT_EXISTING -5

#define CHAR_BACKSPACE 8

#define g_stdo ::stdo
#define g_stde ::stde
#define g_available ::available
#define g_read ::read

class Driver{
public:
	virtual char* get_path();
	virtual int get_type();
};

class Terminal: public Driver{
public:
	virtual void stdo(char* d);
	virtual void stde(char* d);
	virtual char read();
	virtual bool available();
	int get_type(){
		return DRIVER_TYPE_TERM;
	}
	void set_blinking(bool blink){}
	int set_font(unsigned char** font, int height, int length){
		return ERROR_NOT_SUPPORTED;
	}
};

class Keyboard: public Driver{
public:
	/*
	* Returns ASCII value, or special keycode.
	*/
	virtual int read();
	virtual bool available();
	int get_type(){
		return DRIVER_TYPE_KEYBOARD;
	}
};

class FileHandle{
public:
	virtual void read(char* buffer, int n);
	virtual void write(char* buffer, int n);
	virtual int tell();
	virtual void flush();
	virtual void close();
	void write(char* str){
		this->write(str, len(str));
	}
};

class FileSystem: public Driver{
public:
	virtual char* ls(char* dir, int index);
	virtual bool isfile(char* dir);
	virtual bool exists(char* dir);
	virtual int mkdir(char* dir);
	virtual FileHandle* open(char* dir, int mode);
	
	int get_type(){
		return DRIVER_TYPE_FS;
	}
};

class VoidTerminal: public Terminal{
public:
	void stdo(char* d){}
	void stde(char* d){}
	char read(){return 0;}
	bool available(){return false;}
	char* get_path(){
		return "null";
	}
};

#include "graphics_drivers.h"

void set_primary_terminal(Terminal* term);
void set_root_fs(FileSystem* fs);

int num_drivers();
Driver* get_driver(int i);
int add_driver(Driver* driver);
int rm_driver(int driver_id);
int load_drivers();

#include "../include/kernel_functions.h"
#include "drivers.c"

#endif
