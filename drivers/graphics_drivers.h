
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
	
	int tile_color(unsigned short a, unsigned char b);
	
	void print(char* x);
	void println(char* x);
	void println(const char* x);
	void print(const char* x);
	
	
	int get_type();
	
	char* get_desc();
};

extern char drv_display_cnt;

class GraphicsDisplay: public Terminal{
public:
	void display_setup(GraphicsHardware* host, int stde_color = -1, int stdo_color = -1);
	void stdo(char* d);
	void stde(char* d);
	char read();
	bool available();
	int get_type();
	void set_blinking(bool blink);
	int load_font(unsigned char** font, int height, int length);
	char* get_path();
protected:
	char display_id;
	char name[6];
	GraphicsHardware* host;
	
	int stde_c, stdo_c;
};
