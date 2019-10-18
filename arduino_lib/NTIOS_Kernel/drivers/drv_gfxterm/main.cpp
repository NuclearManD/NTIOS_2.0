
class GraphicsTerm: public GraphicsDisplay{
public:
	

	bool available(){
		return kbd->available();
	}

	char read(){
		return kbd->read();
	}

	void term_postinit(){
		GraphicsHardware* host=0;
		for(int i=0;i<num_drivers();i++){
			Driver* driver = get_driver(i);
			if(driver->get_type()==DRIVER_TYPE_GRAPHICS_HARDWARE){
				host = (GraphicsHardware*)driver;
			}
		}
		kbd = 0;
		for(int i=0;i<num_drivers();i++){
			Driver* driver = get_driver(i);
			if(driver->get_type()==DRIVER_TYPE_KEYBOARD){
				kbd = (Keyboard*)driver;
			}
		}
		
		if(kbd==0){
			g_stde("No keyboard driver!  Will not set up graphics terminal.\n");
		}else if(host!=0){
			display_setup(host);
			strcpy(name, "term0");
			g_stdo("Started graphics terminal on /dev/");
			g_stdo(host->get_path());
			g_stdo("\n");
			set_primary_terminal(this);
		}else{
			g_stde("No graphics hardware found!  Will not set up graphics terminal.\n");
		}
	}
protected:
	Keyboard* kbd;
};

GraphicsTerm term0;
