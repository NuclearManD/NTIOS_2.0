#define MAN_INSTALLED

char** man_topics;
char** man_text;
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
	man_topics = (char**)malloc(0);
	man_text = (char**)malloc(0);
	n_topics = 0;
}

void man_add_topic(char* topic, char* text){
	man_topics = (char**)realloc(man_topics, (n_topics+1)*sizeof(char*));
	man_text = (char**)realloc(man_text, (n_topics+1)*sizeof(char*));
	man_topics[n_topics] = topic;
	man_text[n_topics] = text;
	n_topics++;
}
