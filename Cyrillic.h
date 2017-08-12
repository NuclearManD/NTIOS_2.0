#include <avr/pgmspace.h>
char* Nalloc(unsigned short length);
#define ALPH_LENGTH 93
const PROGMEM byte cyrillic [ALPH_LENGTH][8]= {
  {
    0b00000,
    0b00100,
    0b01010,
    0b10001,
    0b11111,
    0b10001,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b11111,
    0b10000,
    0b11110,
    0b10001,
    0b10001,
    0b11110,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b11110,
    0b10001,
    0b11110,
    0b10001,
    0b10001,
    0b11110,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b11111,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b01110,
    0b01010,
    0b10010,
    0b11111,
    0b10001,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b11111,
    0b10000,
    0b11111,
    0b10000,
    0b10000,
    0b11111,
    0x05 // 5 pixels long
  },
  {
    0b01010,
    0b00000,
    0b11111,
    0b10000,
    0b11111,
    0b10000,
    0b11111,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10101,
    0b10101,
    0b11111,
    0b11111,
    0b10101,
    0b10101,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b11110,
    0b00001,
    0b01110,
    0b00001,
    0b00001,
    0b11110,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10001,
    0b10011,
    0b10101,
    0b10101,
    0b11001,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b01010,
    0b00100,
    0b10001,
    0b10011,
    0b10101,
    0b11001,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10011,
    0b10100,
    0b11100,
    0b10100,
    0b10010,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b01111,
    0b01001,
    0b01001,
    0b01001,
    0b01001,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10001,
    0b11011,
    0b10101,
    0b10001,
    0b10001,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10001,
    0b10001,
    0b11111,
    0b10001,
    0b10001,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b01110,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b01110,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b11111,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b11110,
    0b10001,
    0b10001,
    0b11110,
    0b10000,
    0b10000,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b01110,
    0b10001,
    0b10000,
    0b10000,
    0b10001,
    0b01110,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0b00100,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10001,
    0b01010,
    0b00110,
    0b00010,
    0b00100,
    0b11000,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b00100,
    0b01110,
    0b10101,
    0b10101,
    0b01110,
    0b00100,
    0x05 // 5 pixels long
  },
  {
    0b10001,
    0b10001,
    0b01010,
    0b00100,
    0b01010,
    0b10001,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10010,
    0b10010,
    0b10010,
    0b10010,
    0b11111,
    0b00001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10001,
    0b10001,
    0b01111,
    0b00001,
    0b00001,
    0b00001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10101,
    0b10101,
    0b10101,
    0b10101,
    0b11111,
    0b00000,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10101,
    0b10101,
    0b10101,
    0b10101,
    0b11111,
    0b00001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b11000,
    0b01000,
    0b01110,
    0b01001,
    0b01110,
    0b00000,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10001,
    0b10001,
    0b10001,
    0b11001,
    0b10101,
    0b11001,
    0x05 // 5 pixels long
  },
  {
    0b000,
    0b100,
    0b100,
    0b100,
    0b110,
    0b101,
    0b110,
    0x03 // 3 pixels long
  },
  {
    0b00000,
    0b01110,
    0b10001,
    0b00001,
    0b01111,
    0b00001,
    0b11110,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b10010,
    0b10101,
    0b10101,
    0b11101,
    0b10101,
    0b10010,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b01111,
    0b10001,
    0b01111,
    0b00101,
    0b01001,
    0b10001,
    0x05 // 5 pixels long
  },
  // BEGIN LOWERCASE
  {
    0b00000,
    0b00000,
    0b01110,
    0b00001,
    0b01111,
    0b10011,
    0b01101,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b00000,
    0b01111,
    0b10000,
    0b11110,
    0b10001,
    0b11110,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b00000,
    0b11110,
    0b10001,
    0b11110,
    0b10001,
    0b11110,
    0x05 // 5 pixels long
  },
  {
    0b0000,
    0b0000,
    0b1111,
    0b1000,
    0b1000,
    0b1000,
    0b1000,
    0x04 // 4 pixels long
  },
  {
    0b0000,
    0b0000,
    0b0111,
    0b0101,
    0b1001,
    0b1111,
    0b1001,
    0x04 // 4 pixels long
  },
  {
    0b0000,
    0b0000,
    0b1111,
    0b1000,
    0b1111,
    0b1000,
    0b1111,
    0x04 // 4 pixels long
  },
  {
    0b01010,
    0b00000,
    0b11111,
    0b10000,
    0b11111,
    0b10000,
    0b11111,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b00000,
    0b10101,
    0b10101,
    0b11111,
    0b10101,
    0b10101,
    0x05 // 5 pixels long
  },
  {
    0b0000,
    0b0000,
    0b1110,
    0b0001,
    0b0010,
    0b0001,
    0b1110,
    0x04 // 4 pixels long
  },
  {
    0b00000,
    0b00000,
    0b10001,
    0b10011,
    0b10101,
    0b11001,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b01010,
    0b00100,
    0b10001,
    0b10011,
    0b10101,
    0b11001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b00000,
    0b10011,
    0b10100,
    0b11100,
    0b10010,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b0000,
    0b0000,
    0b0111,
    0b0101,
    0b0101,
    0b0101,
    0b1001,
    0x04 // 4 pixels long
  },
  {
    0b00000,
    0b00000,
    0b10001,
    0b11011,
    0b10101,
    0b10001,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b0000,
    0b0000,
    0b1001,
    0b1001,
    0b1111,
    0b1001,
    0b1001,
    0x04 // 4 pixels long
  },
  {
    0b00000,
    0b00000,
    0b00000,
    0b01110,
    0b10001,
    0b10001,
    0b01110,
    0x05 // 5 pixels long
  },
  {
    0b0000,
    0b0000,
    0b1111,
    0b1001,
    0b1001,
    0b1001,
    0b1001,
    0x04 // 4 pixels long
  },
  {
    0b00000,
    0b00000,
    0b10110,
    0b11001,
    0b10110,
    0b10000,
    0b10000,
    0x05 // 5 pixels long
  },
  {
    0b0000,
    0b0000,
    0b0110,
    0b1001,
    0b1000,
    0b1001,
    0b0110,
    0x04 // 4 pixels long
  },
  {
    0b00000,
    0b00000,
    0b00000,
    0b11111,
    0b00100,
    0b00100,
    0b00100,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b00000,
    0b10001,
    0b01010,
    0b00100,
    0b01000,
    0b10000,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b00000,
    0b00100,
    0b01110,
    0b10101,
    0b01110,
    0b00100,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b00000,
    0b10001,
    0b01010,
    0b00100,
    0b01010,
    0b10001,
    0x05 // 5 pixels long
  },
  {
    0b0000,
    0b0000,
    0b1010,
    0b1010,
    0b1010,
    0b1111,
    0b0001,
    0x04 // 4 pixels long
  },
  {
    0b0000,
    0b0000,
    0b1001,
    0b1001,
    0b0111,
    0b0001,
    0b0001,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b00000,
    0b10101,
    0b10101,
    0b10101,
    0b11111,
    0b00000,
    0x05 // 5 pixels long
  },
  {
    0b00000,
    0b00000,
    0b10101,
    0b10101,
    0b10101,
    0b11111,
    0b00001,
    0x05 // 5 pixels long
  },
  {
    0b0000,
    0b0000,
    0b1100,
    0b0100,
    0b0110,
    0b0101,
    0b0110,
    0x04 // 4 pixels long
  },
  {
    0b00000,
    0b00000,
    0b10001,
    0b10001,
    0b11001,
    0b10101,
    0b11001,
    0x05 // 5 pixels long
  },
  {
    0b000,
    0b000,
    0b100,
    0b100,
    0b110,
    0b101,
    0b110,
    0x03 // 3 pixels long
  },
  {
    0b0000,
    0b0000,
    0b1110,
    0b0001,
    0b0111,
    0b0001,
    0b1110,
    0x04 // 4 pixels long
  },
  {
    0b00000,
    0b00000,
    0b10010,
    0b10101,
    0b11101,
    0b10101,
    0b10010,
    0x05 // 5 pixels long
  },
  {
    0b0000,
    0b0000,
    0b0111,
    0b1001,
    0b0111,
    0b0101,
    0b1001,
    0x04 // 4 pixels long
  },
  // CERIAN ALPHABET BEGIN HERE
  {
    0b00001,
    0b00010,
    0b00100,
    0b01010,
    0b10001,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b11111,
    0b10001,
    0b11111,
    0b10001,
    0b11111,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b00000,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b11111,
    0b10001,
    0b10001,
    0b10001,
    0b11111,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b11111,
    0b01000,
    0b00100,
    0b01000,
    0b11111,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b00010,
    0b00100,
    0b11111,
    0b00100,
    0b00100,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b11111,
    0b10001,
    0b11111,
    0b00001,
    0b01001,
    0b00101,
    0b00011,
    0x05
  },
  {
    0b10000,
    0b10000,
    0b11111,
    0b10001,
    0b10001,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b00100,
    0b00010,
    0b00000,
    0b00100,
    0b00100,
    0b00100,
    0b01000,
    0x05
  },
  {
    0b11111,
    0b00010,
    0b00010,
    0b00010,
    0b10010,
    0b01010,
    0b00110,
    0x05
  },
  {
    0b1001,
    0b1010,
    0b1110,
    0b1001,
    0b1010,
    0b0000,
    0b0000,
    0x04
  },
  {
    0b1,
    0b1,
    0b1,
    0b1,
    0b1,
    0b0,
    0b0,
    0x01
  },
  {
    0b10001,
    0b10101,
    0b10001,
    0b10001,
    0b10001,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b1000,
    0b1000,
    0b1100,
    0b1010,
    0b1001,
    0b0000,
    0b0000,
    0x04
  },
  {
    0b00001,
    0b11111,
    0b10001,
    0b10001,
    0b11111,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b11111,
    0b10001,
    0b11111,
    0b10000,
    0b10000,
    0b0000,
    0b0000,
    0x05
  },
  {
    0b111110,
    0b100010,
    0b111110,
    0b000010,
    0b000010,
    0b000010,
    0b000011,
    0x06
  },
  {
    0b11111,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b00001,
    0b00010,
    0b00101,
    0b01000,
    0b10100,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b11111,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0x05
  },
  {
    0b11111,
    0b10000,
    0b10000,
    0b10000,
    0b11111,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b10001,
    0b10010,
    0b10100,
    0b11000,
    0b10000,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b10101,
    0b10101,
    0b10101,
    0b10101,
    0b01011,
    0b00001,
    0b01110,
    0x05
  },
  {
    0b10101,
    0b01010,
    0b00100,
    0b01010,
    0b10001,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b11100,
    0b00100,
    0b00100,
    0b00100,
    0b00111,
    0b00000,
    0b00000,
    0x05
  },
  {
    0b101,
    0b100,
    0b101,
    0b100,
    0b101,
    0b000,
    0b000,
    0x03
  },
};
Sprite* cyrillic_sprites;
byte*   cyrillic_data;
void load_cyrillic_alphabet(){
  cyrillic_sprites=(Sprite*)Nalloc(sizeof(Sprite)*ALPH_LENGTH);
  cyrillic_data=Nalloc(20);
  for(byte i=0;i<ALPH_LENGTH;i++){
    byte clen=pgm_read_byte(&(cyrillic[i][7]));
    cyrillic_sprites[i].binary_image=cyrillic_data;
    cyrillic_sprites[i].set_size(clen,7);
    cyrillic_sprites[i].set_center(7-clen,7);
    cyrillic_sprites[i].fill(0);
    for(byte y=0;y<7;y++){
      byte q=pgm_read_byte(&(cyrillic[i][y]));
      for(byte x=7;x>(7-clen);x--){
        cyrillic_sprites[i].pixel(x,y,bitRead(q,7-x));
      }
      //cyrillic_data[j*2+4]=(x&1)|((x&2)<<1)|((x&4)<<2)|((x&8)<<3);
      //x=x>>4;
      //cyrillic_data[j*2+5]=(x&1)|((x&2)<<1)|((x&4)<<2)|((x&8)<<3);
    }
    cyrillic_sprites[i].upload();
  }
}
void cyrillic_wchr(short x, short y, byte c){
  cyrillic_sprites[c].display(x, y, 0);
}

