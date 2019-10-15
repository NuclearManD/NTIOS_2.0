#include <avr/eeprom.h>
#include <string.h>

#define MAX_RCS_SIZE 4095

EEPROM_rcS::EEPROM_rcS(int mode){
	loc = 0;
	this->mode = mode;
}
int EEPROM_rcS::read(char* buffer, int n){
	if(mode!=FILE_MODE_RD)return ERROR_NOT_SUPPORTED;
	int i;
	for(i=0;(i<n)&&(loc<MAX_RCS_SIZE);loc++,i++){
		char c = (char)eeprom_read_byte((unsigned char*)loc);
		if((c==0)||(c==0xFF)){
			break;
		}
		buffer[i] = c;
	}
	return i;
}
int EEPROM_rcS::write(char* buffer, int n){
	if(mode!=FILE_MODE_WR)return ERROR_NOT_SUPPORTED;
	int i;
	for(i=0;(i<n)&&(loc<MAX_RCS_SIZE);loc++,i++){
		eeprom_update_byte((unsigned char*)loc, buffer[i]);
	}
	eeprom_update_byte((unsigned char*)loc, 0xFF);
	
	return i;
}
int EEPROM_rcS::tell(){
	return loc;
}
void EEPROM_rcS::flush(){} // we flush as we go
void EEPROM_rcS::close(){
	delete this;  // you CANNOT use the file after closing.  Garunteed crash!
}

char* rcS_str = "rcS";

char* EEPROM_FS::ls(char* dir, int index){
	if(strcmp(dir, ""))return 0;
	if(index==0)return ".";
	if(index==1)return rcS_str;
	return 0;
}
bool EEPROM_FS::isfile(char* dir){
	stdo(dir);
	return !strcmp(dir, rcS_str);
}
bool EEPROM_FS::exists(char* dir){
	stdo(dir);
	return !strcmp(dir, rcS_str);
}
int EEPROM_FS::mkdir(char* dir){
	return ERROR_NOT_SUPPORTED;
}
FileHandle* EEPROM_FS::open(char* dir, int mode){
	if(strcmp(dir, rcS_str))return 0;
	return new EEPROM_rcS(mode);
}
