
class RootFS: public FileSystem{
public:
	char* ls(char* dir, int index){
		if(!dircmp(dir, "/")){
			if(index==1)
				return "dev";
			else if(index>1)
				return 0; // error, does not exist
		}else if(!dircmp(dir, "dev")){
			if(index>0){
				index--;
				if(index>=num_drivers())
					return 0; // does not exist
				return get_driver(index)->get_path();
			}
		}else{
			return 0; // error
		}
		return ".";
	}
	bool isfile(char* dir){
		return false;
	}
	bool exists(char* dir){
		if(!(dircmp(dir, "/")&&dircmp(dir, "/dev")))return true;
		return false;
	}
	int mkdir(char* dir){
		return ERROR_NOT_SUPPORTED;
	}
	FileHandle* open(char* dir, int mode){
		return (FileHandle*)0;
	}
	
	char* get_path(){
		return "rootfs";
	}
};

RootFS root;

void preinit_root_fs(){
	set_root_fs(&root);
}
