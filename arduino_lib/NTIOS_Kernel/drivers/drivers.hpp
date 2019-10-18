#ifndef DRIVERS_H
#define DRIVERS_H

#define DRIVER_TYPE_TERM 0
#define DRIVER_TYPE_FS 1
#define DRIVER_TYPE_GRAPHICS_HARDWARE 2
#define DRIVER_TYPE_KEYBOARD 3
#define DRIVER_TYPE_GPIO 4

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1

#define FILE_MODE_WR 0
#define FILE_MODE_RD 1

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

#ifdef __NTIOS_INCLUDE__
	#include "kernel_functions.hpp"
	#include "platform_proto.hpp"
#else
	#include "../kernel_functions.hpp"
	#include "../platform_proto.hpp"
#endif

class Driver{
public:
	virtual char* get_path() = 0;
	virtual int get_type() = 0;
};

class Terminal: public Driver{
public:
	virtual void stdo(char* d) = 0;
	virtual void stde(char* d) = 0;
	virtual char read() = 0;
	virtual bool available() = 0;
	int get_type();
	void set_blinking(bool blink);
	int set_font(unsigned char** font, int height, int length);
};

class Keyboard: public Driver{
public:
	/*
	* Returns ASCII value, or special keycode.
	*/
	virtual int read();
	virtual bool available();
	int get_type();
};

class FileHandle{
public:
	virtual int read(char* buffer, int n) = 0;
	virtual int write(char* buffer, int n) = 0;
	virtual int tell() = 0;
	virtual void flush() = 0;
	virtual void close() = 0;
	int write(char* str);
};

class VoidTerminal: public Terminal{
public:
	void stdo(char* d);
	void stde(char* d);
	char read();
	bool available();
	char* get_path();
};

class GPIOPort: public Driver{
public:
	virtual int get_size() = 0;
	virtual int set_mode(int pin, int mode) = 0;
	virtual int get_mode(int pin) = 0;
	virtual int set_pin(int pin, bool value) = 0;
	virtual bool get_pin(int pin) = 0;
	
	int get_type();
};

#include "graphics_drivers.hpp"
#include "../fs/fs.hpp"

void set_primary_terminal(Terminal* term);
void set_root_fs(FileSystem* fs);

int num_drivers();
Driver* get_driver(int i);
int add_driver(Driver* driver);
int rm_driver(int driver_id);
int load_drivers();

#endif
