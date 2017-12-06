#ifndef MICROEDIT_H
#define MICROEDIT_H
#include "Arduino.h"
#include <NMT_GFX.h>
#include <PS2Keyboard.h>
#include <SD.h>
extern NMT_GFX vga;
extern PS2Keyboard kbd;
extern int freeRam();
void micro_edit(char* name);
#endif
