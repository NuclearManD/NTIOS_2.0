
char curdir[128];
char* fs_resolve(char* fs_buffer, char* loc){
  char tmp[32];
  int index=0;
  int copied=0;
  int last_index=0;
  if(loc[0]!='/'){
    for(unsigned int i=0;i<=strlen(curdir);i++){
      if(curdir[i]=='/'||curdir[i]==0){
        if(!strcmp(tmp,".")){
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
        tmp[copied]=curdir[i];
        copied++;
      }
    }
    copied=0;
  }
  for(unsigned int i=0;i<=strlen(loc);i++){
    if(loc[i]=='/'||loc[i]==0){
      if(!strcmp(tmp,".")){
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
  if(loc[strlen(loc)-1]=='/'){
    if(fs_buffer[index-1]!='/')
      fs_buffer[index]='/';
    fs_buffer[index+1]=0;
  }else if(fs_buffer[index-1]=='/'){
    fs_buffer[index-1]=0;
  }else
    fs_buffer[index]=0;
  return fs_buffer;
}

bool dircmp(char* a, char* b){
  char bufa[len(a)+16];
  char bufb[len(b)+16];
  fs_resolve(bufa, a);
  fs_resolve(bufb, b);
  // TODO: finish this
}

bool exists(char* path){
  char buffer[len(path)+16];
  return root_fs->exists(fs_resolve(buffer, path));
}
bool isfile(char* path){
  char buffer[len(path)+16];
  return root_fs->isfile(fs_resolve(buffer, path));
}
char* ls(char* path, int i){
  char buffer[len(path)+16];
  return root_fs->ls(fs_resolve(buffer, path), i);
}
int mkdir(char* path){
  char buffer[len(path)+16];
  return root_fs->mkdir(fs_resolve(buffer, path));
}
