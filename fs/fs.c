#include "tmpfs.c"


FileSystem** mount_fs;
char** mount_path;
int mount_num = 0;

int curdir_len = 1;
char curdir[128];

char* sym_curdir = ".";

void fs_setup(){
	curdir[0] = '/';
	curdir[1] = 0;
	mount_path = (char**)malloc(0);
	mount_fs = (FileSystem**)malloc(0);
}

// REQUIRES an absolute path, or the mounted filesystem will be unreachable!
int mount(FileSystem* fs, const char* path){
	int v = mount_num;
	mount_num++;
	mount_path = (char**)realloc(mount_path, mount_num*sizeof(char*));
	mount_fs = (FileSystem**)realloc(mount_fs, mount_num*sizeof(FileSystem*));
	mount_path[v] = (char*)path;
	mount_fs[v] = fs;
	return v;
}

char* fs_resolve_raw(char* fs_buffer, char* loc, bool force_nodir){
	char tmp[32];
	int index=0;
	int copied=0;
	int last_index=0;
	if(loc[0]!='/'){
		strcpy(fs_buffer, curdir);
		index = strlen(curdir);
	}
	for(unsigned int i=0;i<=strlen(loc);i++){
		if(loc[i]=='/'||loc[i]==0){
			if(!strcmp(tmp,sym_curdir)){
				;
			}else if(!strcmp(tmp,"..")){
				index=last_index;
			}else{
				last_index=index;
				for(int j=0;j<copied;j++){
					fs_buffer[index]=tmp[j];
					index++;
				}
				if(fs_buffer[index-1]!='/'){
					fs_buffer[index]='/';
					index++;
				}
			}
			copied=0;
		}else{
			tmp[copied]=loc[i];
			copied++;
		}
	}
	if((loc[strlen(loc)-1]=='/') && (!force_nodir)){
		if(fs_buffer[index-1]!='/'){
			fs_buffer[index]='/';
			fs_buffer[index+1]=0;
		}else
			fs_buffer[index]=0;
	}else if((index>1)&&(fs_buffer[index-1]=='/')){
		fs_buffer[index-1]=0;
	}else
		fs_buffer[index]=0;
	return fs_buffer;
}

char* fs_resolve(char* fs_buffer, char* loc){
	return fs_resolve_raw(fs_buffer, loc, false);
}

// returns true if path starts with root
bool dirrootcmp(char* root, char* path){
	char bufa[len(root)+curdir_len+1];
	char bufb[len(path)+curdir_len+1];
	fs_resolve(bufa, root);
	fs_resolve(bufb, path);
	
	/*
	stdo(bufa);
	stdo(" : ");
	stdo(bufb);
	stdo("\n");
	*/

	for(int i=0;;i++){
		if(bufa[i]==0)return true;
		if(bufa[i]!=bufb[i])return false;
	}
}

bool dircmp(char* a, char* b){
	char bufa[len(a)+curdir_len+1];
	char bufb[len(b)+curdir_len+1];
	fs_resolve(bufa, a);
	fs_resolve(bufb, b);
	for(int i=0;;i++){
		if(bufa[i]!=bufb[i])return false;
		if(bufa[i]==0)break;
	}
	return true;
}

// returns index where this path is mounted, or -1 if not found
int get_mount_root(char* path){
	for(int i=0;i<mount_num;i++){
		if(dirrootcmp(mount_path[i], path)){
			return i;
		}
		//stdo("no\n");
	}
	return -1;
}

bool exists(char* path){
	if(!strcmp(path, "/"))return true;
	
	char buffer[len(path)+curdir_len+1];
	fs_resolve(buffer, path);
	
	int mount_point = get_mount_root(buffer);
	if(mount_point == -1)return false;
	
	// it does exist: it's a mounted filesystem
	if(dirrootcmp(mount_path[mount_point], buffer))return true;
	
	// adding length of mount point gets the path relative to the mounted file system
	return mount_fs[mount_point]->exists(buffer+len(mount_path[mount_point]));
}
bool is_file(char* path){
	if(!strcmp(path, "/"))return false;
	
	char buffer[len(path)+curdir_len+1];
	fs_resolve(buffer, path);
	
	int mount_point = get_mount_root(buffer);
	if(mount_point == -1)return false;
	
	if(dirrootcmp(mount_path[mount_point], buffer))return false; // no it's a dir

	return mount_fs[mount_point]->isfile(buffer+len(mount_path[mount_point]));
}
bool is_dir(char* path){
	return (exists(path)&&(!is_file(path)));
}

char* ls(char* path, int i){
	if(!strcmp(path, "/")){
		if(i==0) return sym_curdir;
		i--;
		if(i>=mount_num)return 0;
		return mount_path[i]+1;  // skip initial slash
	}
	
	char buffer[len(path)+curdir_len+1];
	fs_resolve_raw(buffer, path, true);
	
	int mount_point = get_mount_root(buffer);
	if(mount_point == -1)return 0;
	
	// adding length of mount point gets the path relative to the mounted file system
	return mount_fs[mount_point]->ls(buffer+len(mount_path[mount_point]), i);
}
int mkdir(char* path){
	if(!strcmp(path, "/")){
		return -100;
	}
	
	char buffer[len(path)+curdir_len+1];
	fs_resolve(buffer, path);
	
	int mount_point = get_mount_root(buffer);
	if(mount_point == -1)return -1;
	
	// adding length of mount point gets the path relative to the mounted file system
	return mount_fs[mount_point]->mkdir(buffer+len(mount_path[mount_point]));
}

bool set_curdir(char* val){
	if(!is_dir(val))return false;
	fs_resolve(curdir, val);
	curdir_len = strlen(curdir);
	return true;
}

FileHandle* fopen(char* path, int mode){
	if(!strcmp(path, "/"))return 0;
	
	char buffer[len(path)+curdir_len+1];
	fs_resolve(buffer, path);
	
	int mount_point = get_mount_root(buffer);
	if(mount_point == -1)return 0;
	
	return mount_fs[mount_point]->open(buffer+len(mount_path[mount_point])+1, mode);
}
