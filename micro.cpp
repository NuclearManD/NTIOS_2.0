#include "micro.h"
#define SCREEN_X_CHARS 42 // NGT20 Gfx Consts
#define SCREEN_Y_CHARS 13
int cursx=0;
int cursy=0;
int file_index=0;
boolean cursor_dirty=false;
boolean print_char(char c,boolean scroll=false){
  if(!(scroll||cursy<SCREEN_Y_CHARS))
    return false; // no more
  if(c=='\t'){
    do{
      print_char(' ');
    }while(cursx%4);
  }else if(c=='\n'||c=='\r'){
    if(cursor_dirty){
      vga.set_cursor_pos(cursx,cursy);
      cursor_dirty=false;
    }
    vga.print('\r');
    if(cursy<SCREEN_Y_CHARS)
      cursy++;
    cursx=0;
  }else{
    if(cursx<SCREEN_X_CHARS||scroll){
      vga.print(c);
      cursx++;
    }else
      cursor_dirty=true;
  }
  return true;
}
void print_file(File f){
  vga.clear();
  vga.set_cursor_pos(cursx,cursy);
  f.seek(file_index);
  while(f.available()){
    if(!print_char(f.read()))
      break;
    file_index++;
  }
}
void micro_edit(char* name){
  if(!SD.exists(name)){
    vga.print(name);
    vga.println(" does not exist.");
    return;
  }
  cursx=cursy=0;
  File file=SD.open(name);
  print_file(file);
  boolean curs_state=false;
  long curs_time=millis()+250;
  file_index=0;
  cursx=cursy=0;
  vga.set_cursor_pos(cursx,cursy);
  while(true){
    if(kbd.available()){
      char c=kbd.read();
      if(c==PS2_ESC){
        file.close();
        break;
      }
    }
    if(curs_time<millis()){
      curs_time=millis()+250;
      curs_state=!curs_state;
      if(curs_state){
        vga.print('_');
      }else{
        vga.set_color(0);
        vga.fill_box(cursx*6+6,cursy*13+13,cursx*6+12,cursy*13+26);
        vga.set_color(1);
        file.seek(file_index);
        vga.set_cursor_pos(cursx,cursy);
        if(file.available())
          vga.print(file.read());
        vga.set_cursor_pos(cursx,cursy);
      }
    }
  }
  file.close();
  vga.clear();
}
