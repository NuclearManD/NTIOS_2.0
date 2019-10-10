#ifndef PLATFORM_H
#define PLATFORM_H

//  Use this file to define or do anything that is platform-specific
//#define F_CPU 16000000UL
#define __AVR_ATmega2560__
#include <avr/io.h>

extern int entry(void);

#include "main.cpp"

void* operator new(size_t objsize) { 
    return malloc(objsize); 
} 

void operator delete(void* obj) { 
    free(obj); 
}

#endif
