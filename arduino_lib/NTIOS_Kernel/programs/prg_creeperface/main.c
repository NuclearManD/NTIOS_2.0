
Sprite face;
long cp_score = 65025;
bool alloc_face = false;
long cp_time;
int cpx = 50;
int cpy = 50;
int cpex, cpey;
byte face_buffer[20];

void creeperface_main(char** argv, char* argc){
	cp_score = 65025;
	if (!alloc_face) {
		cpex = random(10, 100);
		cpex = random(10, 80);
		alloc_face = true;
		face.binary_image = face_buffer;
		face.set_size(8, 8);
		face.set_center(4, 4);
		face.fill(0);
		face.pixel(2, 2, 1);
		face.pixel(5, 2, 1);
		face.pixel(2, 5, 1); // this is the exact same sprite from
		face.pixel(5, 5, 1); // the old NuclearGames CreeperFace
		face.pixel(3, 4, 1); // game.  Good game, glad I didn't
		face.pixel(4, 4, 1); // loose it.  Now I make it again :D
		face.upload(&vga);
	}
	cp_time = millis();
	
	while(true){
		if (available()) {
			char c = read();
			// check for some of the special keys
			if (c == PS2_LEFTARROW) {
				cpx = cpx - 2;
			} else if (c == PS2_RIGHTARROW) {
				cpx = cpx + 2;
			} else if (c == PS2_UPARROW) {
				cpy = cpy - 2;
			} else if (c == PS2_DOWNARROW) {
				cpy = cpy + 2;
			}
		}
		cp_score = cp_score - (millis() - cp_time);
		cp_time = millis();
		if (cpx == cpex && cpy == cpey) {
			alert(("You win! Score: " + String(cp_score)).c_str());
		}
		if (cp_score < 0) {
			alert("You failed.  GG.");
		}
	}
	
	cpex = random(10, cols - 10);
	cpex = random(10, rows - 10);
	cp_score = 65025;
}
