#include "NTIKernel.hpp"
#include "fs/fs.cpp"
#include "drivers/drivers.cpp"
#include "programs/program.cpp"

#define TERM_KBD_BUF 128


char loop_term_cmd[TERM_KBD_BUF];

unsigned short loop_term_cnt = 0;

int entry(void) {
	k_init();
	stdo(curdir);
	stdo("$ ");
	while(true){
		if (available()){
			char c = read();
			if ((c == '\n') || (c == '\r')) {
				loop_term_cmd[loop_term_cnt] = 0;
				stdo("\n");
				system(loop_term_cmd);
				loop_term_cnt = 0;
				stdo(curdir);
				stdo("$ ");
			} else if (c == CHAR_BACKSPACE) {
				if (loop_term_cnt > 0) {
					loop_term_cnt--;
					char ch[] = {c, 0};
					stdo(ch);
				}
			} else {
				if (loop_term_cnt < TERM_KBD_BUF) {
					loop_term_cmd[loop_term_cnt] = c;
					loop_term_cnt++;
					char ch[] = {c, 0};
					stdo(ch);
				}
			}
		}
	}
	return -1;  // something went wrong if we're here, return negative.
}


unsigned char data = 0;

void (*reset)()=0;

VoidTerminal void_term;
Terminal* primary_term = &void_term;

void set_primary_terminal(Terminal* term){
	primary_term = term;
}

void stdo(char* d){
	primary_term->stdo(d);
}
void stde(char* d){
	primary_term->stde(d);
}
void stdo(const char* d){
	primary_term->stdo((char*)d);
}
void stde(const char* d){
	primary_term->stde((char*)d);
}
char read(){
	return primary_term->read();
}
bool available(){
	return primary_term->available();
}

char* int_to_str(int i, char* o){
	const char* a="0123456789ABCDEF";
	o[0] = a[(i >> 12) & 0xF];
	o[1] = a[(i >> 8) & 0xF];
	o[2] = a[(i >> 4) & 0xF];
	o[3] = a[i & 0xF];
	o[4]=0;
	return o;
}
extern int freeRam();

unsigned short len(char* d){
	unsigned short i=0;
	while(d[i]!=0)
		i++;
	return i;
}
int to_int(char* str){
	int out=0;
	for(unsigned char i=0;i<len(str);i++){
		out+=pow(10,i)*(str[i]-'0');
	}
	return out;
}

char* fs_resolve(char* fs_buffer, char* loc);

bool dircmp(char* a, char* b);

bool exists(char* path);
bool is_file(char* path);
bool is_dir(char* path);
char* ls(char* path, int i);
int mkdir(char* path);

char buf_0x10[256];

void system(char* inp){
	char* args[10];
	unsigned char cnt=1;
	char* src=buf_0x10;
	args[0]=src;
	
	for(unsigned short i=0; i<len(inp); i++){
		char c=inp[i];
		if(c!=' ')
			src[i]=c;
		else{
			src[i]=0;
			args[cnt]=i+1+src;
			
			cnt++;
			while(inp[i+1]==' ')
				i++;
		}
	}
	src[len(inp)]=0;
	if(!strcmp(args[0],"mem")){
		stdo("RAM unsigned chars free: ");
		char buf[10];
	snprintf(buf, 10,	"%i", freeRam());
		stdo(buf);
	}else if(!strcmp(args[0],"ls")){
		char* path;
		if(cnt<2)
			path = curdir;
		else
			path = args[1];
		if(ls(path, 0)==0){
			stde("Not a directory: '");
			stde(path);
			stde("'");
		}else{
			int i = 1;
			while(true){
				char* fname = ls(path, i);
				if(fname==0)break;
				stdo(fname);
				stdo("\n");
				i++;
			}
		}
	}else if(!strcmp(args[0],"cd")){
		if(cnt<2){
			stde("Usage: cd [directory]");
		}else{
			if(!set_curdir(args[1]))
				stde("Not a directory.");
		}
	}else if(!strcmp(args[0],"cat")){
		if(cnt<2){
			stde("Usage: cat [file]");
		}else{
			FileHandle* file = fopen(args[1], FILE_MODE_RD);
			if(file==0){
				stde("File not found.");
			}else{
				char buf[16];
				while(file->read(buf, 16)>0){
					stdo(buf);
				}
				file->close();
			}
		}
	}else if(!strcmp(args[0],"mkdir")){
		if(cnt<2)
			stde("Usage: mkdir [directory name]");
		else{
			int result = mkdir(args[1]);
			if(result!=0){
				char buf[10];
				stde("Error ");
				snprintf(buf, 10,	"%i", result);
				stde(buf);
				stde(" in mkdir");
			}
		}
	}else{
		// try program execution
		execute_program(args, cnt);
	}
	stdo("\n");
nonewline:
	return;
}
void k_init() {
	fs_setup();
	load_drivers();
	add_driver(new VoidTerminal());

	stdo("Running program setup...\n");
	init_programs();

	stdo("Entering user mode...\n\n");
}
