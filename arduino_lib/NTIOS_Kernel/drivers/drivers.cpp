/*
This file organizes the drivers.
*/


// includes

#include "drivers.hpp"
#include "driver_classes.cpp"
#include <stdlib.h>



#define NUM_STARTUP_DRIVERS 0

Driver** drivers;
int _num_drivers = NUM_STARTUP_DRIVERS;

char drv_display_cnt = 0;

int num_drivers(){
	return _num_drivers;
}

Driver* get_driver(int i){
	if((i>=_num_drivers)||(i<0))return (Driver*)0;
	
	return drivers[i];
}

int add_driver(Driver* driver){
	_num_drivers++;
	drivers = (Driver**)realloc(drivers, sizeof(Driver*)*_num_drivers);
	drivers[_num_drivers-1] = driver;
	return _num_drivers-1;
}

int rm_driver(int driver_id){
	if(driver_id<NUM_STARTUP_DRIVERS)return ERROR_NOT_REMOVABLE;
	if(driver_id>=_num_drivers)return ERROR_NOT_EXISTING;
	_num_drivers--;
	drivers[driver_id] = drivers[_num_drivers];
	drivers = (Driver**)realloc(drivers, sizeof(Driver*)*_num_drivers);
	return 0;
}

int load_drivers(){
	drivers = (Driver**)malloc(sizeof(Driver*)*NUM_STARTUP_DRIVERS);
	
	preinit_platform_drivers();


	init_platform_drivers();


	postinit_platform_drivers();



	return _num_drivers;
}
