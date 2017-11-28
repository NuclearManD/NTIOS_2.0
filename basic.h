#ifndef BASIC_CPP
#define BASIC_CPP
#include <avr/pgmspace.h>
#include <Arduino.h>
int compile(char* src, char* dst);
int executeCompiledCode(byte* pgm, int length);
void setup_basic(void (println_f)(char*));
#endif
