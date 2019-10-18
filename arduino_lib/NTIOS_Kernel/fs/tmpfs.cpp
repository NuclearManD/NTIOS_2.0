#include "driver_api.hpp"

// WIP for now

/*
class TMPFS_Read_Handle: public FileHandle{
public:
	int read(char* buffer, int n);
	int write(char* buffer, int n);
	int tell();
	void flush();
	void close();
};

class TMPFS_Write_Handle: public FileHandle{
public:
	int read(char* buffer, int n);
	int write(char* buffer, int n);
	int tell();
	void flush();
	void close();
};

class FileSystem: public Driver{
public:
	virtual char* ls(char* dir, int index) = 0;
	virtual bool isfile(char* dir) = 0;
	virtual bool exists(char* dir) = 0;
	virtual int mkdir(char* dir) = 0;
	FileHandle* open(char* dir, int mode){
		if(mode==FILE_MODE_WR){
			
		}
	}
	
	int get_type();
protected:
	
};
*/
