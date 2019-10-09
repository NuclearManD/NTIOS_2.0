#ifndef DRIVER_API
#define DRIVER_API

#include "../drivers/drivers.h"

int num_drivers();
Driver* get_driver(int i);
int add_driver(Driver* driver);
int rm_driver(int driver_id);

#endif
