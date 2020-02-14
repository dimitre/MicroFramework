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
	
	beginShader();


	fill(255,0,80);

	a += .0002;
	push();
//	translate (width/2, height/2,-1*width);
	rotateX ((mouseDragY)/height * 180.0);
	rotateY ((mouseDragX)/width * 180.0);
	
//	fill(255);
	
//	float aresta = 16.0;
	int max = 16;
	
	float aresta = 8.0;
	for (auto & interval : { 8, 4, 2, 1  }) {
		lineWidth(interval);
		float arestaInterval = aresta * interval;
		for (int x=-max; x<=max; x+=interval) {
			float r = map(x, -max, max, 100, 255);
			for (int y=-max; y<=max; y+=interval) {
//				if (rand() % 10 > 8)
				{
					push();
					translate(x*aresta, y*aresta);
					float rot = x*1.5 + y*2.2 + a*300.0;
					rotateX(rot*1);
					rotateY(rot*1.3);
					rotateZ(rot*1.7);
					fill(r, 255.0-r, mouseX, 200);
		//			rect(0,0,aresta*.2,aresta*1.5);
		//			rect(0,0,aresta*1.5,aresta*.2);
	//				float deslocamento = mouseY / 3.0;
	//				line(0,0,deslocamento,0);
	//				circle(0, 0, arestaInterval *.4);
	//				translate(deslocamento,0,0);
					box(arestaInterval*.4);
		//			line(0,0,aresta,0);
					pop();
				}
			}
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
