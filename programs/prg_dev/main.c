
#include <string.h>

#include "driver_api.h"

char* driver_types[] = {
	"terminal",
	"filesystem",
	"graphics",
	"keyboard",
	"gpio port"
};

int dev_main(char** argv, int argc){
	if(argc<2){
		stdo("usage: dev [path]\n       dev -l");
		return 0;
	}
	char* path = argv[1];
	if(!strcmp(path, "-l")){
		for(int i=0;i<num_drivers();i++){
			stdo(get_driver(i)->get_path());
			stdo("\n");
		}
	}else{
		for(int i=0;i<num_drivers();i++){
			if(!strcmp(path, get_driver(i)->get_path())){
				stdo("type: ");
				stdo(driver_types[get_driver(i)->get_type()]);
				return 0;
			}
		}
		stde("Not a driver path: ");
		stde(path);
		stde("\nUse 'dev -l' to list driver paths.");
		return -1;
	}
	return 0;
}

void dev_init(){
	#ifdef MAN_INSTALLED
	man_add_topic("dev", "\t\tdev - a tool for driver management\n\
Usage: dev -l    : lists driver paths\n\
       dev [driver path]  : info on driver\n\
\n\
\tThere is not much here yet. Come again soon :)");
	#endif
}
