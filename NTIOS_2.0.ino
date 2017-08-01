#include "NTIKernel.h"
void setup() {
  // put your setup code here, to run once:
  k_init();
  println("System is booting with GEAR...");
  gr.addProcess(shell_upd,shell_fup,(char*)"Shell",__empty,P_ROOT|P_KILLER);
  //println("Starting system processes...");
  //gr.addProcess(__empty,usage_daemon,(char*)"daemon0",P_ROOT);
  println("Setup done, please wait...");
  println("Any key to open shell.");
  while(!kbd.available());
  kbd.read();
  for(byte i=0;i<gr.processes;i++){
    gr.ftimes[i]=millis()+gr.fupd_rate;
  }
  sw_gui(0);
  /*stdo=(void (*)(const char*))term_print;
  stde=(void (*)(const char*))term_error;
  stdo("test...\r");
  system("sudo");
  system("sudo -f");
  system("lsps");
  system("terminate 0");
  while(true);*/
}

void loop() {
  gr.run();
  if(gr.processes==0){
    vga.clear();
    vga.println("Computer has crashed:\n  No more running processes.\n  Any key to reset arduino.");
    while(kbd.available())kbd.read();
    while(!kbd.available());
    reset();
  }
  if(kbd.available()){
    last_key=kbd.read();
  }else
    last_key=0;
  if(sel_process>=gr.processes){
    sel_process=0;
    sw_gui(0);
  }
}
bool dir=false;
String apps[5]=   {"TaskMan" ,"reboot", "cmd"};
void (*upd[5])()= {taskupd   ,__empty , __empty};
void (*fupd[5])()={taskfu    ,__empty , __empty};
void (*stp[5])()= {__empty   ,0       , term};//,__q,__q,__q};
byte napps=3;
void shell_fup(){
  if(sel_process==0){
    if(redraw){
      selected=0;
      window(0,1,15,6);
      vga.set_color(2);
      vga.set_cursor_pos(0,1);
      vga.print("OPEN PROGRAM:");
      vga.set_cursor_pos(1,2);
      vga.set_color(3);
      vga.print(apps[0]);
      vga.set_color(2);
      for(byte i=1;i<napps;i++){
        vga.set_cursor_pos(1,2+i);
        vga.print(apps[i]);
      }
      term_close();
      redraw=false;
    }
  }else{
    if(redraw){
      redraw=false;
    }
  }
}
void shell_upd(){
  if(sel_process==0){  // Program Opener
    if(available()){
      uint16_t c=read();
      byte q=selected;
      if(c==PS2_DOWNARROW){
        selected++;
        if(selected>=napps)
          selected=0;
      }else if(c==PS2_UPARROW){
        selected--;
        if(selected==255)
          selected+=napps;
      }else if(c==PS2_ENTER){
        q=selected=launch((*upd[selected]),(*fupd[selected]),apps[selected].c_str(),(*stp[selected]));
        
        if(selected>0){
          sw_gui(1);
          vga.clear();
        }else
          alert("ERROR: too many processes!");
      }else if(c==(PS2_TAB)){
        selected=0;
        term_close();
        sw_gui(0);
        sel_process+=1;
        if(selected>=gr.processes)
          selected=0;
        vga.clear();
      }
      if(q!=selected){
        for(byte i=0;i<napps;i++){
          if(selected==i)
            vga.set_color(3);
          else
            vga.set_color(2);
          vga.set_cursor_pos(1,2+i);
          vga.print(apps[i]);
        }
      }
    }
  }else{ // Background
    if((last_key==PS2_ESC)&&(sel_process!=0)){
      gr.kill(sel_process);
      selected=0;
      term_close();
      sw_gui(0);
      sel_process=0;
    }else if(last_key==(PS2_TAB)){
      selected=0;
      term_close();
      sw_gui(0);
      sel_process+=1;
      if(selected>=gr.processes)
        selected=0;
    }
  }
}
long last_task_time=0;
byte last_task_count=0;
byte task_sel=0;
void taskfu(){
  if(last_task_time>millis())
    return;
  if(last_task_count>gr.processes){
    vga.set_color(0);
    vga.fill_box(112,(gr.processes+3)*13-6,219,(last_task_count+3)*13+3);
  }
  window(18,1,35,2+gr.processes);
  for(int i=0;i<gr.processes&&i<8;i++){
    if(task_sel==i)
      vga.set_color(3);
    else
      vga.set_color(2);
    vga.set_cursor_pos(18,1+i);
    vga.print(48+i);
    if(sel_process!=i)
      vga.print(':');
    else
      vga.print('*');
    vga.print(gr.getName(i));
    if((!strcmp(gr.getName(i),"TaskMan"))&&i!=gr.cprocess){
      alert((char*)"TaskMan already running.");
      gr.kill(i);
    }
  }
  vga.set_color(3);
  vga.set_cursor_pos(18,1+gr.processes);
  vga.print("Free RAM : ");
  vga.print(String(freeRam()));
  last_task_time=millis()+1000;
  last_task_count=gr.processes;
}
void taskupd(){
  byte q=task_sel;
  if(available()){
    uint16_t c=read();
    if(c==PS2_DOWNARROW){
      task_sel++;
    }else if(c==PS2_UPARROW){
      task_sel--;
    }else if(c==PS2_DELETE){
      int res=gr.kill(task_sel);
      if(res>=0)
        sel_process=res;  // update selected process
      else if(res==ACCESS_DENIED){
        system("sudo -f");
        system((String("terminate ")+String(task_sel)).c_str());
        alert("Self-hacked.");
      }else if(res==INVALID_ARGUMENT)
        alert("Error: A Glitch");
      else
        alert("Unknown Error");
      q=task_sel+1; // redraw IMMEDIATELY
    }
  }
  if(task_sel>=gr.processes)
    task_sel=0;
  else if(task_sel==255)
    task_sel+=gr.processes;
  if(q!=task_sel){
    last_task_time=0; // Allow next call to work...
    taskfu();         // Redraw graphics
  }
}
char* term_cmd="";
unsigned short term_cnt=0;
void term_print(char* d){
  vga.set_color(3);
  print(d);
  vga.set_color(2);
}
void term_error(char* d){
  vga.set_color(2);
  print(d);
}
void term(){
  if(!okcancel("CMD needs to stop GEAR.")){
    gr.kill(gr.cprocess); // die, it canceled.
    return;
  }else{
    stdo=term_print;
    stde=term_error;
    term_cmd=Nalloc(128);
    println("Terminal Started.\nLeave with 'exit -L'");
  }
  while(true){
    if(available()){
      uint16_t c=kbd.read();
      if(c=='\n'||c=='\r'){
        if(!strcmp(term_cmd,"exit -L"))
          break;
        system(term_cmd);
        term_cmd[0]=0;
        term_cnt=0;
        print("> ");
      }else{
        term_cmd[term_cnt]=c;
        term_cnt++;
        print(c);
      }
    }
  }
  gr.kill(gr.cprocess);// stop
  gear_stopwait();// fix GEAR
}

