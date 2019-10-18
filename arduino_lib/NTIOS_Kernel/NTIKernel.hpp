#ifndef NTI_KERNEL_H
#define NTI_KERNEL_H
//#pragma GCC diagnostic warning "-fpermissive"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "programs/program.hpp"
#include "drivers/drivers.hpp"
#include "fs/fs.hpp"
#include "driver_api.hpp"

/*
 * Some quick fixes to be handled later - just to get it to compile.
 */

char* substr(char* arr, int begin, int len);
void Nsystem(char* inp);
unsigned short len(char* d);
int entry(void);

void set_primary_terminal(Terminal* term);

void stdo(char* d);
void stde(char* d);
void stdo(const char* d);
void stde(const char* d);
char read();
bool available();

char* int_to_str(int i, char* o);
extern int freeRam();

unsigned short len(char* d);
int to_int(char* str);

char* fs_resolve(char* fs_buffer, char* loc);

bool dircmp(char* a, char* b);

bool exists(char* path);
bool is_file(char* path);
bool is_dir(char* path);
char* ls(char* path, int i);
int mkdir(char* path);

void system(char* inp);
void k_init();
#endif
