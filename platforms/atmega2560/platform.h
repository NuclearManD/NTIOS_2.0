#ifndef PLATFORM_H
#define PLATFORM_H

#include "drv_uart/drv_uart.cpp"
#include "drv_gpio/drv_gpio.cpp"

extern int entry(void);
extern int mount(FileSystem* fs, const char* path);
int main(void);

class EEPROM_rcS: public FileHandle{
public:
	EEPROM_rcS(int mode);
	int read(char* buffer, int n);
	int write(char* buffer, int n);
	int tell();
	void flush();
	void close();
protected:
	int loc, mode;
};

class EEPROM_FS: public FileSystem{
public:
	char* ls(char* dir, int index);
	bool isfile(char* dir);
	bool exists(char* dir);
	int mkdir(char* dir);
	FileHandle* open(char* dir, int mode);
};

#include "eepromfs.cpp"

#endif
