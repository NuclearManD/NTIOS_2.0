#ifndef BASIC_CPP
#define BASIC_CPP
#include "basic.h"
#define CMD_NOP   0x00
#define CMD_EXIT  0x01
#define CMD_IF    0x02
#define CMD_PRINT 0x03
#define CMD_THEN  0x04
#define CMD_END   0x05
#define CMD_VAR   0x06
#define CMD_ITS   0x07 // int to string
#define CMD_EQ    0x08
#define CMD_QTE   0x09 // quote
#define CMD_STI   0x0A // string to int

#define CMD_NAME  0xFF // name of something


#define MAX_NUM_VARS 32
#define CMD_COUNTER 10 // number of commands excluding CMD_NAME

#define NAME_UNREC_ERR -1
#define INVALID_OP_ERR -2
#define NORML_EXIT_ERR -3


const char cmd_0[] /*PROGMEM*/ = "NOP";
const char cmd_1[] /*PROGMEM*/ = "EXIT";
const char cmd_2[] /*PROGMEM*/ = "IF";
const char cmd_3[] /*PROGMEM*/ = "PRINT";
const char cmd_4[] /*PROGMEM*/ = "THEN";
const char cmd_5[] /*PROGMEM*/ = "END";
const char cmd_6[] /*PROGMEM*/ = "VAR";
const char cmd_7[] /*PROGMEM*/ = "TOSTR";
const char cmd_8[] /*PROGMEM*/ = "=";
const char cmd_9[] /*PROGMEM*/ = "\"";
const char* const command_table[] /*PROGMEM*/ = {cmd_0, cmd_1, cmd_2, cmd_3, cmd_4, cmd_5, cmd_6, cmd_7, cmd_8, cmd_9};
void (*println)(char*);
void setup_basic(void (println_f)(char*)){
  println=println_f;
}
// ONLY USE LETTERS!
boolean strcmpignorecase(char* a, char* b){
  for(int i=0;a[i]!=0&&b[i]!=0;i++){
    // mask off 0x20, it makes lower case letters
    if((a[i]&(char)0xDF)!=(b[i]&(char)0xDF))
      return true;
  }
  return false;
}
int compile(char* src, char* dst){
  //char src[strlen(src_1)];
  //strcpy(src,src_1);
  int num_tokens=0;
  int num_operators=0;
  boolean in_whitespace=true;
  boolean in_quote=false;
  for(int i=0;src[i]!=0;i++){
    char c=src[i];
    if(c=='"'){
      in_quote=!in_quote;
      num_operators++;
      in_whitespace=true;
      num_tokens++;
      if(in_quote)
        num_tokens++;
    }else if(!in_quote){
      switch(c){
        case ' ':
        case '\r':
        case '\n':
        case '\t':
        in_whitespace=true;
        break;
        case ';':                           // comments
          while(src[i]!='\n'&&src[i]!='\r'&&src[i+1]!=0)
            i++;
          break;
        case '/':
        case '*':
        case '+':
        case '-':
        case '!':
        case '^':
        case '=':
        case '%':
        case '&':
        num_tokens++;
        num_operators++;
        in_whitespace=true;// emulate whitespace before and after operators
        break;
        default:
          if(in_whitespace)
            num_tokens++;
          in_whitespace=false;
          break;
      }
    }
  }
  if(!in_whitespace)
    num_tokens++;
  char* tokens[num_tokens];
  char oplist[num_operators*2];
  int token=0;
  num_operators=0;
  in_whitespace=true;
  in_quote=false;
  for(int i=0;src[i]!=0;i++){
    char c=src[i];
    if(c=='"'){
      in_quote=!in_quote;
      in_whitespace=true;// emulate whitespace before and after operators
      src[i]=0;
      oplist[num_operators*2]=c;
      oplist[num_operators*2+1]=0;
      tokens[token]=oplist+(num_operators<<1);
      num_operators++;
      token++;
      if(in_quote){
        tokens[token]=src+i+1;
        token++;
      }
    }else if(!in_quote){
      switch(c){
        case ' ':
        case '\r':
        case '\n':
        case '\t':
          in_whitespace=true;
          src[i]=0;
          break;
        case ';':                           // comments
          while(src[i]!='\n'&&src[i]!='\r'&&src[i+1]!=0)
            i++;
          break;
        case '/':
        case '*':
        case '+':
        case '-':
        case '!':
        case '^':
        case '%':
        case '&':
        case '=':
          in_whitespace=true;// emulate whitespace before and after operators
          src[i]=0;
          oplist[num_operators*2]=c;
          oplist[num_operators*2+1]=0;
          tokens[token]=oplist+(num_operators<<1);
          num_operators++;
          token++;
          break;
        default:
          if(in_whitespace){
            tokens[token]=src+i;
            token++;
            in_whitespace=false;
          }
          break;
      }
    }
  }
  // tokenized.  Now we need to compile it.
  int dst_cnt=0;
  for(int i=0;i<num_tokens;i++){
    boolean found = false;
    for(byte cx=0;cx<CMD_COUNTER;cx++){
      //strcpy_P(buffer, (char*)pgm_read_word(&(command_table[cx])));
      if(!strcmpignorecase(command_table[cx],tokens[i])){
        found=true;
        dst[dst_cnt]=cx;
        dst_cnt++;
        break;
      }
    }
    if(!found){          // name, not command/operator
      dst[dst_cnt]=CMD_NAME;
      dst_cnt++;
      for(int cx=0;tokens[i][cx]!=0;cx++){
        dst[dst_cnt]=tokens[i][cx];
        dst_cnt++;
      }
    }
  }
  return dst_cnt;
}

int compile(File in, File dst){
  if(freeRam()+128<in.size()){
    stde("Not enough RAM for compile to run.");
    return -1;
  }
  char* src=(char*)malloc(in.size());
  for(int i=0;i<in.available();i++){
    src[i]=in.read();
  }
  int num_tokens=0;
  int num_operators=0;
  boolean in_whitespace=true;
  boolean in_quote=false;
  for(int i=0;src[i]!=0;i++){
    char c=src[i];
    if(c=='"'){
      in_quote=!in_quote;
      num_operators++;
      in_whitespace=true;
      num_tokens++;
      if(in_quote)
        num_tokens++;
    }else if(!in_quote){
      switch(c){
        case ' ':
        case '\r':
        case '\n':
        case '\t':
        in_whitespace=true;
        break;
        case ';':                           // comments
          while(src[i]!='\n'&&src[i]!='\r'&&src[i+1]!=0)
            i++;
          break;
        case '/':
        case '*':
        case '+':
        case '-':
        case '!':
        case '^':
        case '=':
        case '%':
        case '&':
        num_tokens++;
        num_operators++;
        in_whitespace=true;// emulate whitespace before and after operators
        break;
        default:
          if(in_whitespace)
            num_tokens++;
          in_whitespace=false;
          break;
      }
    }
  }
  if(!in_whitespace)
    num_tokens++;
  char* tokens[num_tokens];
  char oplist[num_operators*2];
  int token=0;
  num_operators=0;
  in_whitespace=true;
  in_quote=false;
  for(int i=0;src[i]!=0;i++){
    char c=src[i];
    if(c=='"'){
      in_quote=!in_quote;
      in_whitespace=true;// emulate whitespace before and after operators
      src[i]=0;
      oplist[num_operators*2]=c;
      oplist[num_operators*2+1]=0;
      tokens[token]=oplist+(num_operators<<1);
      num_operators++;
      token++;
      if(in_quote){
        tokens[token]=src+i+1;
        token++;
      }
    }else if(!in_quote){
      switch(c){
        case ' ':
        case '\r':
        case '\n':
        case '\t':
          in_whitespace=true;
          src[i]=0;
          break;
        case ';':                           // comments
          while(src[i]!='\n'&&src[i]!='\r'&&src[i+1]!=0)
            i++;
          break;
        case '/':
        case '*':
        case '+':
        case '-':
        case '!':
        case '^':
        case '%':
        case '&':
        case '=':
          in_whitespace=true;// emulate whitespace before and after operators
          src[i]=0;
          oplist[num_operators*2]=c;
          oplist[num_operators*2+1]=0;
          tokens[token]=oplist+(num_operators<<1);
          num_operators++;
          token++;
          break;
        default:
          if(in_whitespace){
            tokens[token]=src+i;
            token++;
            in_whitespace=false;
          }
          break;
      }
    }
  }
  // tokenized.  Now we need to compile it.
  int dst_cnt=0;
  for(int i=0;i<num_tokens;i++){
    boolean found = false;
    for(byte cx=0;cx<CMD_COUNTER;cx++){
      //strcpy_P(buffer, (char*)pgm_read_word(&(command_table[cx])));
      if(!strcmpignorecase(command_table[cx],tokens[i])){
        found=true;
        dst.write(cx);
        dst_cnt++;
        break;
      }
    }
    if(!found){          // name, not command/operator
      dst.write(CMD_NAME);
      dst_cnt++;
      for(int cx=0;tokens[i][cx]!=0;cx++){
        dst.write(tokens[i][cx]);
        dst_cnt++;
      }
    }
  }
  return dst_cnt;
}
void loadName(char* d, char* s, int* i){
  byte da=0;
  for(i[0];s[i[0]]>' ';i[0]++){
    d[da]=s[i[0]];
    da++;
  }
  d[da]=0;
}
void its(int i,char* o){
  char* a="0123456789ABCDEF";
  o[0] = a[(i >> 12) & 0xF];
  o[1] = a[(i >> 8) & 0xF];
  o[2] = a[(i >> 4) & 0xF];
  o[3] = a[i & 0xF];
  o[4]=0;
}
int sti(char* in){
  int o=0;
  for(byte i=0;i<4;i++){
    byte val=(in[i]&0xDF)-'0';// only capital letters
    if(val>15)
      val-=7;
    o|=(val)<<(i<<2);
  }
  return o;
}
boolean isNumeric(char* in){
  for(byte i=0;i<4;i++){
    char c=in[i];
    if(('0'>c||c>'9')&&('A'>c||c>'F'))
      return false;
  }
  return true;
}
byte heap[1024];
int heap_top=0;
int resolveOne(byte* code, int* count, char** varnames, int* varvals, byte* num_vars){
  if(count[0]<0)// crash!
    return 0;
  byte cmd=code[count[0]];
  count[0]++;
  char tmp[64];
  int i_qte=0;
  byte index=0;
  boolean found=false; // search for variable to see if it is already defined
  char* retval;
  switch(cmd){
    case CMD_NOP:
      break;
    case CMD_EXIT:
      count[0]=NORML_EXIT_ERR;
      return 0;
    case CMD_PRINT:
      println((char*)resolveOne(code,count/* count is already a pointer*/,varnames,varvals,num_vars));
      break;
    case CMD_QTE:
      count[0]++;// skip 0xFF
      for(count[0];code[count[0]]!=CMD_QTE;count[0]++){
        tmp[i_qte]=code[count[0]];
        i_qte++;
      }
      tmp[i_qte]=0;
      strcpy(heap+heap_top,tmp);// allocate on program heap
      retval=heap+heap_top;
      heap_top+=strlen(tmp)+1;
      count[0]++;// don't leave on a quote
      return retval;
    case CMD_VAR:   // time to make a string variable!
      count[0]++;
      loadName(tmp,code,count);
      for(byte i=0;i<num_vars[0];i++){
        if(!strcmp(varnames[i],tmp)){
          index=i;
          found=true;
          break;
        }
      }
      if(!found){     // add new variable
        strcpy(heap+heap_top,tmp);// allocate on program heap
        index=num_vars[0];// save index of variable
        varnames[index]=heap+heap_top;
        num_vars[0]++;
        heap_top+=strlen(tmp)+1;
      }
      if(code[count[0]]==CMD_EQ){
        count[0]++;
        varvals[index]=resolveOne(code, count, varnames, varvals, num_vars);
      }
      return varvals[index];
    case CMD_ITS:
      its(resolveOne(code, count, varnames, varvals, num_vars),tmp);
      strcpy(heap+heap_top,tmp);// allocate on program heap
      retval=heap+heap_top;
      heap_top+=strlen(tmp)+1;
      return retval;
    case CMD_NAME: // note that it can also be a numeric constant
      loadName(tmp,code,count);
      if(isNumeric(tmp))
        return sti(tmp);
      for(byte i=0;i<num_vars[0];i++){
        if(!strcmp(varnames[i],tmp)){
          return varvals[i];
        }
      }
      println("Undefined: ");
      println(tmp);
      count[0]=NAME_UNREC_ERR;
      return 0;
    default:
      println("Invalid Opcode Error");
      count[0]=INVALID_OP_ERR;
      return 0;
  }
  return 0; // nothing to return usually.
}
int executeCompiledCode(byte* pgm, int length){
  int counter=0;
  byte num_vars=0;
  char* varnames[MAX_NUM_VARS];
  int  varvals[MAX_NUM_VARS];
  while(counter<length){
    resolveOne(pgm,&counter,varnames, varvals,&num_vars);
    if(counter<0){
      return counter;
    }
  }
  return 0;
}
#endif
