#define MAN_INSTALLED

#include <string.h>
#include <stdlib.h>

const char** man_topics;
const char** man_text;
int n_topics;

int man_main(char** argv, int argc){
	if(argc<2){
		stdo("usage: man [topic]\n       man --list");
		return 0;
	}
	char* topic = argv[1];
	if(!strcmp(topic, "--list")){
		for(int i=0;i<n_topics;i++){
			stdo(man_topics[i]);
			stdo("\n");
		}
	}else{
		for(int i=0;i<n_topics;i++){
			if(!strcmp(man_topics[i], topic)){
				stdo(man_text[i]);
				return 0;
			}
		}
		stde("Not a topic: ");
		stde(topic);
		stde("\nUse 'man --list' to list topics.");
		return -1;
	}
	return 0;
}

void man_init(){
	man_topics = (const char**)malloc(0);
	man_text = (const char**)malloc(0);
	n_topics = 0;
}

void man_add_topic(const char* topic, const char* text){
	man_topics = (const char**)realloc(man_topics, (n_topics+1)*sizeof(const char*));
	man_text = (const char**)realloc(man_text, (n_topics+1)*sizeof(const char*));
	man_topics[n_topics] = topic;
	man_text[n_topics] = text;
	n_topics++;
}
