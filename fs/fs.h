#ifndef FS_H
#define FS_H

class FileSystem{
public:
	virtual char* ls(char* dir, int index) = 0;
	virtual bool isfile(char* dir) = 0;
	virtual bool exists(char* dir) = 0;
	virtual int mkdir(char* dir) = 0;
	virtual FileHandle* fopen(char* dir, int mode) = 0;
	FileSystem* opendir(char* dir){
		return 0;
	}
};

#endif
