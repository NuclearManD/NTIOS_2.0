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
int pos_in_file=0;// stores the beginning of the top line of the current window
void fix_screen_position(char* data, int begin){
  int numy=0,numx=0;
  for(int i=0;data[i]!=0&&i<begin;i++){
    if(data[i]=='\n'||data[i]=='\r'){
      numy++;
      numx=0;
    }else
      numx++;
  }
  while(numy>cursy+SCREEN_Y_CHARS)
    cursy++;
  while(numy<cursy)
    cursy--;
  while(numx>cursx+SCREEN_X_CHARS)
    cursx++;
  while(numx<cursx)
    cursx--;
}
void print_file(char* f){
  vga.clear();
  vga.set_cursor_pos(cursx,cursy);
  int loc=file_index;
  cursor_dirty=false;
  
  for(loc;loc>0&&f[loc]!='\n';loc--);// goto beginning of current line
  
  int tcx,tcy;// temporary cursor positions
  while(f[loc]!=0){
    if(!print_char(f[loc]))
      break;
    loc++;
    if(file_index==loc){
      tcx=cursx;
      tcy=cursy;
    }
  }
  cursx=tcx;
  cursy=tcy;
}
void micro_edit(char* name){
  if(!SD.exists(name)){
    vga.print(name);
    vga.println(" does not exist.");
    return;
  }
  File file=SD.open(name);
  if(file.size()+256<freeRam()/2){
    vga.println("Not enough memory!");
    file.close();
    return;
  }
  char data[file.size()+freeRam()/2-256];// use as much RAM as is safe
  int index=0;
  while(file.available()){
    data[index]=file.read();
    index++;
  }
  file.close();
  pos_in_file=cursx=cursy=0; // reset everything to top of file
  print_file((char*)data);
  boolean curs_state=false;
  long curs_time=millis()+250;
  file_index=0;
  cursx=cursy=0;
  vga.set_cursor_pos(cursx,cursy);
  while(true){
    if(kbd.available()){
      char c=kbd.read();
      if(c==PS2_ESC){
        break;
      }if(c==PS2_LEFTARROW){
        if(file_index>0){
          file_index--;
          print_file(data);
        }
      }else if(c==PS2_RIGHTARROW){
        if(file_index<index){// index is file length
          file_index++;
          print_file(data);
        }
      }else if(c==8){
        file_index--;
        index--; // file is one byte shorter
        strcpy(data+file_index,data+file_index+1);
        print_file(data);
      }else{
        file_index++;
        index++;// file is one byte longer
        for(int i=index+1;i>file_index;i--){
          data[i]=data[i-1];
        }
        data[file_index]=c;
        print_file(data);
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

