
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h" // for attachInterrupt, FALLING
#else
#include "WProgram.h"
#endif


class RootFS: public FileSystem{
public:
	char* ls(char* dir){
		if(!strcmp(dir, "/"))
			return "dev";
		else if(!strcmp(dir, "/dev/")){
			String out = "";
			for(int i=0;i<num_drivers();i++){
				out = out + get_driver(i)->get_path() + ',';
			}
			return out.substring(0, out.length()-1).c_str();
		}else{
			return "";
		}
	}
	bool isfile(char* dir){
		return false;
	}
	bool exists(char* dir){
		return false;
	}
	int mkdir(char* dir){
		return ERROR_NOT_SUPPORTED;
	}
	FileHandle* open(char* dir, int mode){
		return (FileHandle*)0;
	}
	
	char* get_path(){
		return "rootfs";
	}
};

RootFS root;

void preinit_root_fs(){
	set_root_fs(&root);
}
