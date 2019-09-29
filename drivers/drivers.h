#ifndef DRIVERS_H
#define DRIVERS_H

#define DRIVER_TYPE_TERM 0
#define DRIVER_TYPE_FS 1

#define NOT_ERROR 0
#define ERROR_NOT_SUPPORTED -1

#define CHAR_BACKSPACE 8

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
	virtual char* ls(char* dir);
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
		return "";
	}
};

void set_primary_terminal(Terminal* term);
void set_root_fs(FileSystem* fs);

int num_drivers();
Driver* get_driver(int i);
int load_drivers();

#include "../include/kernel_functions.h"
#include "drivers.c"

#endif
