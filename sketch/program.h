float easyX, easyY;
float mouseDragX, mouseDragY;
float mouseX, mouseY;
float tempo;
float a = 200;

ofFbo fbo;


struct rectangle {
	glm::vec2 pos;
	glm::vec2 dimensions;
	glm::vec2 pos2;
	
//	bool inside(glm::vec2 & p) const {
	bool inside(glm::vec2 p)  {
		return (p.x > pos.x && p.x < pos2.x) && (p.y > pos.y && p.y < pos2.y);
	}
	
	void draw() {
		//
		rect(pos, dimensions);
	}
	
	void setPos(glm::vec2 p) {
		pos = p;
		pos2 = pos + dimensions;
	}
	
	rectangle(glm::vec2 p, glm::vec2 d) : pos(p), dimensions(d) {
		pos2 = pos + dimensions;
//		cout << "new rect" << endl;
//		cout << pos.x << " : " << pos.y << endl;
//		cout << dimensions.x << " : " << dimensions.y << endl;
//		cout << pos2.x << " : " << pos2.y << endl;
	};
	
	friend std::ostream& operator<< (std::ostream &o, const rectangle &r)
	{
		return o << "rectangle " << r.pos.x << ", " << r.pos.y << ", " << r.dimensions.x << ", " << r.dimensions.y << endl;
	}
};


struct element {
public:
	rectangle rect = rectangle(glm::vec2(0,0), glm::vec2(200,20));
	rectangle rect2 = rectangle(glm::vec2(0,0), glm::vec2(200,20));
	glm::vec2 pos;
	color cor = color(255,0,0);
	color cor2 = color(0,0,255);
	element() {}
	element(glm::vec2 p) : pos(p) {
		rect2.setPos(pos);
		rect.setPos(pos);
//		rect2.pos = rect.pos = pos;
		rect2.dimensions.x = random(0,200);
	}
	void draw() {
		fill(cor);
		rect.draw();
		fill(cor2);
		rect2.draw();
	}
	
	void checkMouse(glm::vec2 mouse) {
		if (rect.inside(mouse)) {
			cor = color(random(0,255), random(0,255), random(0,255));
		}
	}
};

element elements[10];
//vector <element> elements;

void mouseclick(int button,int state,int x,int y) {
	if (state == GLUT_DOWN) {
//		cout << "mouseclick" << endl;
		for (auto & e : elements) {
			e.checkMouse(glm::vec2(mouseX, mouseY));
		}
		if (button == GLUT_RIGHT_BUTTON) {

		}
	}
}


void setup() {
//	setupMidi();
	cout << "this is setup" << endl;
	
	
	for (int a=0; a<10; a++) {
		int x = 20;
		int y = 20 + a*30;
		elements[a] = element(glm::vec2(x,y));
	}
//	fbo.allocate(410,330);
//	setupShader();
//	test.init();
}


void mousedrag (int x, int y) {
	mouseDragX = x -width/2;
	mouseDragY = y -height/2;
}

void mousemove(int x, int y) {
	mouseX = x;
	mouseY = y;
}


void desenha() {

//	sendMidi();
	background(0.0);
	clear();
	camera();
//	beginShader();
//	beginShader();
	fill(255,0,80);

	a += .0002;
	push();
//	translate (width/2, height/2,-1*width);
	rotateX ((mouseDragY)/height * 180.0);
	rotateY ((mouseDragX)/width * 180.0);
	
	int max = 16;
	float aresta = 8.0;
	for (auto & interval : { 8, 4, 2, 1  }) {
		lineWidth(interval);
		float arestaInterval = aresta * interval;
		for (int x=-max; x<=max; x+=interval) {
			float r = remap(x, -max, max, 100, 255);
			for (int y=-max; y<=max; y+=interval) {
				if (rand() % 10 > mouseX/90.0)
				{
					push();
					translate(x*aresta, y*aresta);
					float rot = x*1.5 + y*2.2 + a*300.0;
					rotateX(rot*1);
					rotateY(rot*1.3);
					rotateZ(rot*1.7);
					fill(r, 255.0-r, mouseX, 100);
					box(arestaInterval*.4);
					pop();
				}
			}
		}
	}
	pop();
	
	noCamera();
	glDepthFunc(GL_ALWAYS);
//	translate(-400,-200);
	
//	for (int a=0; a<10; a++) {
//		fill(0,255,0);
//		rect(20,20,200,30);
//
//		fill(255,0,255);
//		float w = random(0,200);
////		cout << rand() << endl;
////		cout << w << endl;
//		rect(20,20,w,30);
//
//		translate(0,40);
//
//	}
	
	glEnable(GL_DEPTH_TEST);
}


void draw() {
	easyX += (mouseX-easyX)/20.0;
	easyY += (mouseY-easyY)/20.0;
//	fbo.begin();
//	desenha();
//	fbo.end();
//
//	fbo.draw();

//	test.prepare();
	desenha();
	fill(255);
	
	
	for (auto & e : elements) {
		e.draw();
	}
//	test.final();
}
