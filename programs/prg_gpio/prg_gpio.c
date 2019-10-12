
#include <string.h>

#include "driver_api.h"
#include "kernel_functions.h"

const char* modes[] = {
	"input",
	"output"
};

int gpio_main(char** argv, int argc){
	if(argc<2){
		stdo("usage:\n gpio [path]\n gpio -l\n gpio -s [path] [pin] [value]\n gpio -m [path] [pin] [mode:int]");
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
	}else if(!strcmp(path, "-s")){
		path = argv[2];
		int pin = to_int(argv[3]);
		int val = to_int(argv[4]);
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
		path = argv[2];
		int pin = to_int(argv[3]);
		int mode = to_int(argv[4]);
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
					stdo(" : ");
					stdo(modes[gpio->get_mode(j)]);
					stdo(" = ");
					stdo(gpio->get_pin(j) ? "TRUE\n" : "FALSE\n");
				}
				return 0;
			}
		}
		stde("Not a driver path: ");
		stde(path);
		stde("\nUse 'gpio -l' to list gpio driver paths.");
		return -1;
	}
	return 0;
}
