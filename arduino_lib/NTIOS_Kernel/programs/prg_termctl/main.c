#include "driver_api.hpp"
#include "kernel_functions.hpp" // new and delete on AVR

#include <stdio.h>

int ls_termctl_instance = 0;

class TermCtl: public Terminal{
public:
	TermCtl(Terminal* in, Terminal* out){
		input = in;
		output = out;
		snprintf(name, 7, "tctl%i", ls_termctl_instance);
		ls_termctl_instance++;
	}
	void stdo(char* d){
		output->stdo(d);
	}
	void stde(char* d){
		output->stde(d);
	}
	char read(){
		return input->read();
	}
	bool available(){
		return input->available();
	}
	char* get_path(){
		return name;
	}
protected:
	Terminal* input;
	Terminal* output;
	char name[7];
};

int termctl_main(char** argv, int argc){
	if(argc<2){
		stdo("usage: termctl -m [in] [out]\n       termctl -l\n       termctl -u [dev]\n       termctl -r [dev]");
		return 0;
	}
	char* cmd = argv[1];
	if(!strcmp(cmd, "-l")){
		for(int i=0;i<num_drivers();i++){
			Driver* dev = get_driver(i);
			if(dev->get_type()==DRIVER_TYPE_TERM){
				stdo(dev->get_path());
				stdo("\n");
			}
		}
	}else if(!strcmp(cmd, "-m")){
		if(argc==4){
			Terminal* input = 0;
			Terminal* output = 0;
			bool failure = false;
			
			for(int i=0;i<num_drivers();i++){
				Driver* dev = get_driver(i);
				if(dev->get_type()==DRIVER_TYPE_TERM){
					if(!strcmp(argv[2], dev->get_path())){
						input = (Terminal*)dev;
					}
					if(!strcmp(argv[3], dev->get_path())){
						output = (Terminal*)dev;
					}
				}
			}
			
			if(input==0){
				failure = true;
				stde(argv[2]);
				stde(" is not a valid terminal.\n");
			}
			if(output==0){
				failure = true;
				stde(argv[3]);
				stde(" is not a valid terminal.");
			}
			if(!failure){
				TermCtl* new_term = new TermCtl(input, output);
				int result = add_driver(new_term);
				if(result<0){
					stde("Unknown error!");
					return result-100;
				}else{
					stdo(new_term->get_path());
				}
			}else return -1;
		}else{
			stde("termctl -m [in] [out]");
			return -1;
		}
	}else if(!strcmp(cmd, "-r")){
		if(argc==3){
			if(memcmp("tctl", argv[2], 4)==0){
				for(int i=0;i<num_drivers();i++){
					Driver* dev = get_driver(i);
					if(dev->get_type()==DRIVER_TYPE_TERM){
						if(!strcmp(argv[2], dev->get_path())){
							int result = rm_driver(i);
							if(result<0){
								stde("Error removing ");
								stde(argv[2]);
								if(result==ERROR_NOT_REMOVABLE)
									stde(": Not removable.");
								else
									stde(": Unknown error.");
								return result-100;
							}else
								return 0;
						}
					}
				}
			}
			// if we're here then the terminal is not tctl or does not exist.
			stde(argv[2]);
			stde(" is not a tctl terminal.");
			return -1;
		}else{
			stde("termctl -r [dev]");
			return -1;
		}
	}else if(!strcmp(cmd, "-u")){
		if(argc==3){
			for(int i=0;i<num_drivers();i++){
				Driver* dev = get_driver(i);
				if(dev->get_type()==DRIVER_TYPE_TERM){
					if(!strcmp(argv[2], dev->get_path())){
						stdo("Switching terminal to ");
						stdo(dev->get_path());
						set_primary_terminal((Terminal*)dev);
						return 0;
					}
				}
			}
			// if we're here then the terminal is not tctl or does not exist.
			stde(argv[2]);
			stde(" is not a terminal.");
			return -1;
		}else{
			stde("termctl -r [dev]");
			return -1;
		}
	}else{
		stde(argv[1]);
		stde("?");
	}
	return 0;
}

void termctl_init(){
	#ifdef MAN_INSTALLED
/*	man_add_topic("dev", "\t\tdev - a tool for driver management\n\
Usage: dev -l    : lists driver paths\n\
       dev [driver path]  : info on driver\n\
\n\
\tThere is not much here yet. Come again soon :)");*/
	#endif
}
