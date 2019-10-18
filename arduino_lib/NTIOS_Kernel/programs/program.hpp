#ifndef PROGRAM_H
#define PROGRAM_H


#include <string.h>

#ifdef __NTIOS_INCLUDE__
	#include "kernel_functions.hpp"
#else
	#include "../kernel_functions.hpp"
#endif

int execute_program(char** argv, int argc);
void init_programs();

#endif
