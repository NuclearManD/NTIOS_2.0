#define MAN_INSTALLED

char** topics;
char** text;
int n_topics;

int man_main(char** argv, int argc){
	if(argc<2){
		stdo("usage: man [topic]\n       man --list");
		return 0;
	}
	char* topic = argv[1];
	if(!strcmp(topic, "--list")){
		for(int i=0;i<n_topics;i++){
			stdo(topics[i]);
			stdo("\n");
		}
	}else{
		for(int i=0;i<n_topics;i++){
			if(!strcmp(topics[i], topic)){
				stdo(text[i]);
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
