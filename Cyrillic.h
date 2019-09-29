#include <avr/pgmspace.h>
#define ALPH_LENGTH 94
const byte cyrillic [ALPH_LENGTH][8] = {
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
    0b00111,
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
    0b10001,
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
  {
    0b001,
    0b000,
    0b101,
    0b100,
    0b101,
    0b100,
    0b101,
    0x03
  },
  {
    0b100,
    0b000,
    0b101,
    0b100,
    0b101,
    0b100,
    0b101,
    0x03
  }
};
Sprite* cyrillic_sprites;
byte*   cyrillic_data;
bool old_syanomian_e = false;
void load_cyrillic_alphabet() {
  cyrillic_sprites = (Sprite*)Nalloc(sizeof(Sprite) * ALPH_LENGTH);
  cyrillic_data = Nalloc(20);
  for (byte i = 0; i < ALPH_LENGTH; i++) {
    byte clen = pgm_read_byte(&(cyrillic[i][7]));
    cyrillic_sprites[i].binary_image = cyrillic_data;
    cyrillic_sprites[i].set_size(clen, 7);
    cyrillic_sprites[i].set_center(7 - clen, 7);
    cyrillic_sprites[i].fill(0);
    for (byte y = 0; y < 7; y++) {
      byte q = pgm_read_byte(&(cyrillic[i][y]));
      for (byte x = 7; x > (7 - clen); x--) {
        cyrillic_sprites[i].pixel(x, y, bitRead(q, 7 - x));
      }
      //cyrillic_data[j*2+4]=(x&1)|((x&2)<<1)|((x&4)<<2)|((x&8)<<3);
      //x=x>>4;
      //cyrillic_data[j*2+5]=(x&1)|((x&2)<<1)|((x&4)<<2)|((x&8)<<3);
    }
    cyrillic_sprites[i].upload();
  }
}
unsigned short alph_x = 0;
unsigned short alph_y = 0;
byte a_lang = 0;
void alph_nl() {
  alph_y += 8;
  alph_x = 0;
}
void alph_wchr(byte c) {
  byte adv = 0;
  if (c < ALPH_LENGTH) {
    cyrillic_sprites[c].display(alph_x, alph_y, 0);
    adv = pgm_read_byte(&(cyrillic[c][7])) + 1;
  } else
    adv = 5;
  alph_x += adv;
  if (alph_x > cols) {
    alph_nl();
  }
}
void set_lang(byte l) {
  a_lang = l;
}
void alph_setcurs(unsigned short x, unsigned short y) {
  alph_x = x;
  alph_y = y;
}
void alph_print(byte c) {
  // This function essentially acts as a converter for bigger functions.
  // It converts ascii to character codes (if they exist).
  // If there is no character code (punctuation etc) then it will use
  // the NGT20 default font/character set.
  // If the alphabet is 0 (default) then the NGT20 default
  // font is always used.
  byte j = 0;
  if (a_lang == 1) {
    if ((c > 96) && (c < 123)) {
      j = 33;
      c -= 32;
    }
    if (c==65)// A -> &A
        j += 0;
    else if (c==66)// B -> &6
        j += 1;
    else if (c==67)// C -> &U
        j += 23;
    else if (c==68)// D -> &D
        j += 4;
    else if (c==69)// E -> &E
        j += 5;
    else if (c==70)// F -> &O1
        j += 21;
    else if (c==71)// G -> (&)@r
        j += 3;
    else if (c==72)// H -> &^N
        j += 10;
    else if (c==73)// I -> &N
        j += 9;
    else if (c==74)// J -> &2.3
        j += 30;
    else if (c==75)// K -> &K
        j += 11;
    else if (c==76)// L -> &L
        j += 12;
    else if (c==77)
        j += 13;
    else if (c==78)
        j += 14;
    else if (c==79)
        j += 15;
    else if (c==80)
        j += 16;
    else if (c==81)// Q -> &R
        j += 32;
    else if (c==82)// R -> &P
        j += 17;
    else if (c==83)// S -> &C
        j += 18;
    else if (c==84)// T -> &T
        j += 19;
    else if (c==85)// U -> &lY
        j += 20;
    else if (c==86)// V -> &B
        j += 2;
    else if (c==87)// W -> &W
        j += 25;
    else if (c==88)// X -> &X
        j += 22;
    else if (c==89)// Y -> &b|
        j += 29;
    else if (c==90)// Z -> &3
        j += 8;
      // begin more
    else if (c==137)// :E ->&:E
        j = 6;
    else if (c==136)// ^e -> &:e
        j = 39;
    else if (c==142)// :A -> &,W
        j = 26;
    else if (c==132)// :a -> &,w
        j = 59;
    else if (c==148)// :o -> &|x
        j = 40;
    else if (c==153)// :O -> &|X
        j = 7;
    else if (c==150)// ^u -> &|o
        j = 64;
    else if (c==154)// :U -> &|O
        j = 31;
    else if (c==164)// ~n -> &'b
        j = 60;
    else if (c==165)// ~N -> &'!b
        j = 27;
    else if (c==128)// ,C -> &!b
        j = 29;
    else if (c==135)// ,c -> &b
        j = 62;
    else if (c==145)// ae -> &|y
        j = 24;
    else if (c==146)// AE -> &|Y
        j = 57;
   else{
      vga.set_cursor_pos(alph_x / 6 -1, alph_y / 8 -1);
      vga.print(c);
      alph_x += 6;
      return;
    }
  } else if (a_lang == 2) {
    if ((c > 96) && (c < 123))
      c -= 32;
    if(c==138){
      j=92;
    }else if(c==144){
      j=93;
    }else if((c > 64) && (c < 91)){
      if ((c == 69) && old_syanomian_e)
        c = 91;
      j = c + 1;
    }else{
      vga.set_cursor_pos(alph_x / 6 -1, alph_y / 8 -1);
      vga.print(c);
      alph_x += 6;
      return;
    }
  } else {
    vga.set_cursor_pos(alph_x / 6 -1, alph_y / 8 -1);
    vga.print(c);
    alph_x += 6;
    return;
  }
  alph_wchr(j);
}
void alph_print(char* d){
  byte c;
  short i=0;
  while(c=d[i]){
    alph_print(d[i]);
    i++;
  }
}
