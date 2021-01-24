float easyX, easyY;
float mouseDragX, mouseDragY;
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
	
	fill(255,0,80);

	a += .001;
	push();
//	translate (width/2, height/2,-1*width);
	rotateX (mouseDragX/height * 180.0);
	rotateY (mouseDragY/width * 180.0);
	
	fill(255);
	
	float aresta = 10.0;
	int max = 12;
	for (int x=-max; x<=max; x++) {
		float r = map(x, -max, max, 180, 255);
//		cout << x << " :: " << r << endl;
		for (int y=-max; y<=max; y++) {
			push();
			translate(x*aresta, y*aresta);
			rotateX(x*10.0 + y*10.0 + a*100.0);
			rotateY(x*10.0 + y*10.0 + a*100.0);
			rotateZ(x*10.0 + y*10.0 + a*100.0);
			fill(r, y*10.0, 100);
			rect(0,0,aresta*.3,aresta*2);
			line(0,0,aresta,0);
			pop();
		}
	}
	
//	for (float y = 1; y < 7000; y++) {
//		//stroke(155, y%255, a);
//		fill(sin(y/9.0)*127 + 127, (int)y/8%255, 100);
//		rotateY (.08 * easyX);
//		rotateX (sin(y*3.0 + a) * 180.0);
//		rotateZ (.1 * easyY);
//		float yy = y/100000.0;
//		translate (yy, -yy, -a/20.0);
//		line(0, 0, 0, 80);
//		rect(0, 0, 5, 5);
////		rect(y/2.0, 0, 23, 23);
//
//	}
	pop();
}

void mousedrag (int x, int y) {
	mouseDragX = x;
	mouseDragY = y;
}

void mousemove(int x, int y) {
	mouseX = x;
	mouseY = y;
}
