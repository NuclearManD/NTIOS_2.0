
#include <string.h>
#include <stdlib.h>

#include "driver_api.hpp"
#include "kernel_functions.hpp"

const char* modes[] = {
	"input ",
	"output"
};

void gpio_usage(){
	stdo("usage:\n gpio [path]\n gpio -l\n gpio -s [path] [pin] [0/1]\n gpio -m [path] [pin] [mode:int]");
}

int gpio_main(char** argv, int argc){
	if(argc<2){
		gpio_usage();
		return 0;
	}
	char* path = argv[1];
	if(!strcmp(path, "-l")){
		for(int i=0;i<num_drivers();i++){
			Driver* dev = get_driver(i);
			if(dev->get_type()==DRIVER_TYPE_GPIO){
				char buffer[4];
				GPIOPort* gpio = (GPIOPort*)dev;
				stdo(gpio->get_path());
				stdo(" : ");
				stdo(itoa(gpio->get_size(), buffer, 10));
				stdo(" pins.");
			}
		}
		return 0;
	}else if(!strcmp(path, "-s")){
		if(argc<5){
			gpio_usage();
			return -1;
		}
		path = argv[2];
		int pin = (int)strtol(argv[3], NULL, 10);
		bool val = argv[4][0]=='1';
		for(int i=0;i<num_drivers();i++){
			Driver* dev = get_driver(i);
			if((dev->get_type()==DRIVER_TYPE_GPIO)&&(!strcmp(path, dev->get_path()))){
				GPIOPort* gpio = (GPIOPort*)dev;
				int result = gpio->set_pin(pin, val);
				if(result!=0){
					char buffer[4];
					stde("Error#");
					stde(itoa(result, buffer, 10));
					stde("\n");
					return 100-result;
				}
				return 0;
			}
		}
	}else if(!strcmp(path, "-m")){
		if(argc<5){
			gpio_usage();
			return -1;
		}
		path = argv[2];
		int pin = (int)strtol(argv[3], NULL, 10);
		int mode = (int)strtol(argv[4], NULL, 10);
		for(int i=0;i<num_drivers();i++){
			Driver* dev = get_driver(i);
			if((dev->get_type()==DRIVER_TYPE_GPIO)&&(!strcmp(path, dev->get_path()))){
				GPIOPort* gpio = (GPIOPort*)dev;
				int result = gpio->set_mode(pin, mode);
				if(result!=0){
					char buffer[4];
					stde("Error#");
					stde(itoa(result, buffer, 10));
					stde("\n");
					return 100-result;
				}
				return 0;
			}
		}
	}else{
		for(int i=0;i<num_drivers();i++){
			Driver* dev = get_driver(i);
			if((dev->get_type()==DRIVER_TYPE_GPIO)&&(!strcmp(path, dev->get_path()))){
				GPIOPort* gpio = (GPIOPort*)dev;
				char buffer[8];
				for(int j=0;j<gpio->get_size();j++){
					stdo(itoa(j, buffer, 10));
					stdo("\t: ");
					stdo(modes[gpio->get_mode(j)]);
					stdo(" = ");
					stdo(gpio->get_pin(j) ? "TRUE\n" : "FALSE\n");
				}
				return 0;
			}
		}
	}
	stde("Path not found.\n");
	return -1;
}
