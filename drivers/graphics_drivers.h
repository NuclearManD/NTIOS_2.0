
#define COLOR_TYPE_BW		0
#define COLOR_TYPE_GREY8	1
#define COLOR_TYPE_GRAY8	1
#define COLOR_TYPE_RGB8		2
#define COLOR_TYPE_NES8		3
#define COLOR_TYPE_GREY16	4
#define COLOR_TYPE_GRAY16	4
#define COLOR_TYPE_RGB16	5
#define COLOR_TYPE_NES16	6


class GraphicsHardware: public Driver{
public:
	virtual int begin();
	virtual int end();
	virtual int get_color_type();
	virtual void set_color(unsigned int color);
	
	virtual void pixel(unsigned int x, unsigned int y);
	
	virtual bool is_connected();
	
	virtual void set_cursor_pos(unsigned int x, unsigned int y);
	
	/**
	 * Font Format
	 * 
	 * {
	 *   0b1101,   // binary pixels
	 *   0b0101,
	 * ...
	 *   0b0010,
	 *   4         // length of this char
	 * },
	 * {
	 * ...
	 * 
	 * ch_height is the number of vertical pixels in each character
	 * length is the number of symbols in the font
	 * 
	 * returns the font ID
	 * 
	 */
	virtual int load_font(unsigned char** font, int ch_height, int length);
	
	/*
	 * Use ID -1 for default, or the value given by load_font for that loaded font.
	 */
	virtual int set_font(int id);
	
	
	// for custom fonts, the first character in the font is ASCII 176
	virtual void print(char x);
	virtual void println(char x);
	
	virtual unsigned int width();
	virtual unsigned int height();
	
	int tile_color(unsigned short a, unsigned char b){
		return ERROR_NOT_SUPPORTED;
	}
	
	void print(char* x){
		int i=0;
		while(x[i]!=0){
			this->print(x[i]);
			i++;
		}
	}
	void println(char* x){
		int i=0;
		while(x[i]!=0){
			this->print(x[i]);
			i++;
		}
		this->print('\n');
	}
	void println(const char* x){this->println((char*)x);}
	void print(const char* x){this->print((char*)x);}
	
	
	int get_type(){
		return DRIVER_TYPE_GRAPHICS_HARDWARE;
	}
	
	char* get_desc(){
		return "unknown";
	}
};

extern char drv_display_cnt;

class GraphicsDisplay: public Terminal{
public:
	void display_setup(GraphicsHardware* host, int stde_color = -1, int stdo_color = -1){
		this->host = host;
		display_id = drv_display_cnt;
		drv_display_cnt+=1;
		name[0]='m';
		name[1]='o';
		name[2]='n';
		name[3]='0'+(display_id/10);
		name[4]='0'+(display_id%10);
		name[5]=0;
		
		int color_type = host->get_color_type();
		
		if(stde_color==-1){
			switch(color_type){
				case COLOR_TYPE_BW:
					stde_color = 1;			// white
					break;
				case COLOR_TYPE_GRAY8:
					stde_color = 192;		// light gray
					break;
				case COLOR_TYPE_RGB8:
					stde_color = 0xE0;		// red
					break;
				case COLOR_TYPE_NES8:
				case COLOR_TYPE_NES16:
					stde_color = 2;			// color 2 (whichever it is)
					break;
				case COLOR_TYPE_GRAY16:
					stde_color = 0xD000;	// light gray
					break;
				case COLOR_TYPE_RGB16:
					stde_color = 0xFC00;	// red
					break;
			}
		}
		if(stdo_color==-1){
			switch(color_type){
				case COLOR_TYPE_BW:
					stdo_color = 1;			// white
					break;
				case COLOR_TYPE_GRAY8:
					stdo_color = 255;		// white
					break;
				case COLOR_TYPE_RGB8:
					stdo_color = 0xFF;		// white
					break;
				case COLOR_TYPE_NES8:
				case COLOR_TYPE_NES16:
					stdo_color = 1;			// color 1 (whichever it is)
					break;
				case COLOR_TYPE_GRAY16:
					stdo_color = 0xFFFF;	// white
					break;
				case COLOR_TYPE_RGB16:
					stdo_color = 0xFFFF;	// white
					break;
			}
		}
		stde_c = stde_color;
		stdo_c = stdo_color;
	}
	void stdo(char* d){
		host->set_color(stdo_c);
		host->print(d);
	}
	void stde(char* d){
		host->set_color(stde_c);
		host->print(d);
	}
	char read(){
		return -1;
	}
	bool available(){
		return false;
	}
	int get_type(){
		return DRIVER_TYPE_TERM;
	}
	void set_blinking(bool blink){}
	int load_font(unsigned char** font, int height, int length){
		return ERROR_NOT_SUPPORTED;
	}
	char* get_path(){
		return name;
	}
protected:
	char display_id;
	char name[6];
	GraphicsHardware* host;
	
	int stde_c, stdo_c;
};
