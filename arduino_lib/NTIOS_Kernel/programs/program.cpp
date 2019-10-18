/*
This file serves to add commands to the system dynamically.
*/


// includes

#include "program.hpp"

#include "prg_termctl/main.c"
#include "prg_man/main.c"
#include "prg_dev/main.c"
#include "prg_gpio/prg_gpio.c"
#include "prg_fsr/main.c"

extern int arduino_exec_pgm(char** argv, int argc);

int execute_program(char** argv, int argc){
	char* cmd = argv[0];
	
	// program load if block
	if(!strcmp(cmd, "termctl")){
		return termctl_main(argv, argc);
	}else 	if(!strcmp(cmd, "man")){
		return man_main(argv, argc);
	}else 	if(!strcmp(cmd, "dev")){
		return dev_main(argv, argc);
	}else 	if(!strcmp(cmd, "gpio")){
		return gpio_main(argv, argc);
	}else 	if(!strcmp(cmd, "fsr")){
		return fsr_main(argv, argc);
	}else {
		arduino_exec_pgm(argv, argc);
	}
	return -1;
}

void init_programs(){
	termctl_init();
	man_init();
	dev_init();

}
