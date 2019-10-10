#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>

class StdTerm: public Terminal{
public:
	void write(char c){
		printf("%c",c);
		fflush(stdout);
	}
	void stdo(char* d){
		printf("%s",d);
		fflush(stdout);
	}

	void stde(char* d){
		printf("%s",d);
		fflush(stdout);
	}

	bool available(){
		struct timeval tv = { 0L, 0L };
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(0, &fds);
		return select(1, &fds, NULL, NULL, &tv);
	}

	char read(){
		int r;
		unsigned char c;
		if ((r = ::read(0, &c, sizeof(c))) < 0) {
			return r;
		} else {
			write(8);
			return c;
		}
	}

	void preinit(){
		
		set_primary_terminal(this);
	}
	
	char* get_path(){
		return "term0";
	}
private:
	char avail;
	bool has_byte;
};

StdTerm term;
