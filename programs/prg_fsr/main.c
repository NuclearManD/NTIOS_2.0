#include <string.h>
#include <stdlib.h>

int fsr_main(char** argv, int argc){
	if(argc<2){
		stdo("usage: fsr [dir]");
		return -1;
	}
	char buffer[128];
	stdo(fs_resolve(buffer, argv[1]));
	return 0;
}
