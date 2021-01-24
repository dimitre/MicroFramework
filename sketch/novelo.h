float easyX, easyY;
float rotX, rotY;
float mouseX, mouseY;
float tempo;

float a = 200;

void setup() {
}

void draw() {
	easyX += (mouseX-easyX)/10.0;
	easyY += (mouseY-easyY)/10.0;
	background(0.0);
	clear();
	camera();
	rotateX(rotX);
	rotateY(rotY);
	
	fill(255,0,80);

	a += .001;
	push();
//	translate (width/2, height/2,-1*width);
	rotateX (2*PI*mouseY/height);
	rotateY (2*PI*mouseX/width);
	
	fill(255);
	for (float y = 1; y < 7000; y++) {
		//stroke(155, y%255, a);
		fill(sin(y/9.0)*127 + 127, (int)y/8%255, 100);
		rotateY (.08 * easyX);
		rotateX (sin(y*3.0 + a) * 180.0);
		rotateZ (.1 * easyY);
		float yy = y/100000.0;
		translate (yy, -yy, -a/20.0);
		line(0, 0, 0, 80);
		rect(0, 0, 5, 5);
//		rect(y/2.0, 0, 23, 23);
	   
	}
	pop();
}

void mousedrag (int x, int y) {
	rotX = x/3.0 + 90;
	rotY = y/3.0 + 90;
}

void mousemove(int x, int y) {
	mouseX = x;
	mouseY = y;
}
