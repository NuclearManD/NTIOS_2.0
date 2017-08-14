uint16_t* ROM_lengths = {10};
const char* ROM_fnames[] = {"null.class","die vert nacht"};
const uint8_t* ROM_data[] = {"1234567890","???"};
byte ROM_file_count=1;
bool ROM_fs_exists(char* name){
  for(byte i=0;i<ROM_file_count;i++){
    if(!strcmp(name,ROM_fnames[i]))
      return true;
  }
  return false;
}
char* ROM_fs_rip(char* name){
  for(byte i=0;i<ROM_file_count;i++){
    if(!strcmp(name,ROM_fnames[i]))
      return ROM_fnames[i];
  }
  return 0;
}
uint16_t ROM_fs_size(char* name){
  for(byte i=0;i<ROM_file_count;i++){
    if(!strcmp(name,ROM_fnames[i]))
      return ROM_lengths[i];
  }
  return 0xEE00;
}

