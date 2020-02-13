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
	rotateX ((mouseDragY)/height * 180.0);
	rotateY ((mouseDragX)/width * 180.0);
	
//	fill(255);
	
	float aresta = 16.0;
	int max = 8;
	lineWidth(2);
	
	for (int x=-max; x<=max; x++) {
		float r = map(x, -max, max, 100, 255);
//		cout << x << " :: " << r << endl;
		for (int y=-max; y<=max; y++) {
			push();
			translate(x*aresta, y*aresta);
			float rot = x*2.0 + y*3.0 + a*300.0;
			rotateX(rot);
			rotateY(rot*1.25);
			rotateZ(rot*1.35);
			fill(r, 255.0-r, mouseX);
//			rect(0,0,aresta*.2,aresta*1.5);
//			rect(0,0,aresta*1.5,aresta*.2);
			
			glutWireCube(aresta*.6);
//			line(0,0,aresta,0);
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
	mouseDragX = x -width/2;
	mouseDragY = y -height/2;
}

void mousemove(int x, int y) {
	mouseX = x;
	mouseY = y;
}
