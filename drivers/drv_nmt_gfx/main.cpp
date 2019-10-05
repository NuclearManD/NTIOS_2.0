#include <NMT_GFX.h>

NMT_GFX gfx;

class NMT_GFX_Driver: public GraphicsHardware{
public:
	int begin(){
		if(has_started)return ERROR_ALREADY_STARTED;
		gfx.begin(11, 10);
		for(int i=0;i<5;i++){
			has_started = is_connected();
			if(has_started){
				break;
			}
		}
		if(has_started)
			return 0;
		else
			return ERROR_NO_HARDWARE;
	}
	int end(){
		has_started = false;
		gfx.end();
		return 0;
	}
	int get_color_type(){
		return COLOR_TYPE_NES16;
	}
	void set_color(unsigned int color){
		if(has_started)gfx.set_color((unsigned char)color);
	}
	
	void pixel(unsigned int x, unsigned int y){
		if(has_started)gfx.pixel((unsigned short)x, (unsigned short)y);
	}
	
	bool is_connected(){
		return gfx.is_connected();
	}
	
	void set_cursor_pos(unsigned int x, unsigned int y){
		if(has_started)gfx.set_cursor_pos((unsigned char)x, (unsigned char)y);
		font_x_curs = (unsigned short)x;
		font_y_curs = (unsigned short)y;
	}
	
	int load_font(unsigned char** font, int ch_height, int length){
		unsigned short start_adr = gfx.__LS_POS__;
		int id = (ch_height<<12) | start_adr;
		
		for(int i=0;i<length;i++){
			// set height, width and center
			
			gfx.w_vram((unsigned short)(i*ch_height + start_adr + 0), 1);
			gfx.w_vram((unsigned short)(i*ch_height + start_adr + 1), ch_height);
			gfx.w_vram((unsigned short)(i*ch_height + start_adr + 2), 0);
			gfx.w_vram((unsigned short)(i*ch_height + start_adr + 3), 0);
			
			// set pixels
			for(int j=0;j<ch_height;j++){
				gfx.w_vram((unsigned short)(i*ch_height + start_adr + 4 + j), font[i][j]);
			}
		}
		return id;
	}
	
	int set_font(int id){
		if(id==-1){
			selected_font=-1;
		}else{
			selected_font = ((unsigned int)id)&0xFFF;
			font_height = ((unsigned int)id)>>12;
		}
		return 0;
	}
	
	void print(char x){
		if(x=='\n')
			x = '\r';
		if(has_started){
			if(selected_font==-1){
				gfx.print(x);
			}else{
				if(x=='\n' || x=='\r'){
					font_y_curs+=8;
				}else if(x==' '){
					font_x_curs+=5;
				}else if(x=='\t'){
					font_x_curs+=15;
					font_x_curs-=font_x_curs%15;
				}else if(x>=(char)176){
					gfx.wait_cmd_done();
					gfx.write(62);
					gfx.write(font_x_curs>>8);
					gfx.write(font_x_curs&255);
					gfx.write(font_y_curs>>8);
					gfx.write(font_y_curs&255);
					gfx.write(0);
					
					// calculate address in VRAM of the character
					unsigned short address = selected_font + font_height*(x-176);
					gfx.write(address>>8);
					gfx.write(address&255);
					font_x_curs+=5;
				}
				if(font_x_curs+5>=width()){
					font_y_curs+=8;
					font_x_curs=0;
				}
			}
		}
	}
	void println(char x){
		if(x=='\n')
			x = '\r';
		if(has_started){
			if(selected_font==-1){
				gfx.println(x);
			}else{
				print(x);
				print('\r');
			}
		}
	}
	
	int tile_color(unsigned short a, unsigned int b){
		if(has_started){
			gfx.tile_color(a, (unsigned char)b);
			return 0;
		}else{
			return ERROR_NO_HARDWARE;
		}
	}
	
	unsigned int width(){
		return 16*gfx.x_tiles();
	}
	unsigned int height(){
		return 16*gfx.y_tiles();
	}
	
	char* get_path(){
		return "nmt_gfx";
	}
	
	char* get_desc(){
		if(has_started)return gfx.get_card_ver();
		else return "NO GPU";
	}
private:
	bool has_started = false;
	int selected_font = -1;
	unsigned char font_height;
	unsigned short font_x_curs = 0;
	unsigned short font_y_curs = 0;
};

NMT_GFX_Driver nmt_gfx;

void nmt_gfx_init(){
	stdo("NMT Graphics: initializing...\n");
	if(nmt_gfx.begin()!=0){
		stde("NMT Graphics: No GPU found!\n");
	}
}
