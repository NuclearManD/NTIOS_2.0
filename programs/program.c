/*
This file serves to add commands to the system dynamically.
*/


// includes
#include "prg_creeperface/main.c"


int execute_program(char** argv, int argc){
	char* cmd = argv[0];
	
	// program load if block
	if(cmd=="creeperface"){
		creeperface_main(argv, argc);
	}else 	{
		stde("Not a command:");
		stde(argv[0]);
	}
	return -1;
}
