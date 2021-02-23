struct app : public microApp {
public:
	float easyX, easyY;
	float mouseDragX, mouseDragY;
	float mouseX, mouseY;
	float tempo;
	float a = 200;

	ofFbo fbo;
	interface u;

	void setup() override {
	//	setupMidi();
		cout << "this is setup" << endl;
		u.setup();
	//	fbo.allocate(410,330);
	//	setupShader();
	//	test.init();
	}

	void mousedrag (int x, int y) override {
		mouseDragX = x -width/2;
		mouseDragY = y -height/2;
	}

	void mousemove(int x, int y) override {
		mouseX = x;
		mouseY = y;
	}

	void mousePressed(glm::vec2 pos) override {
		u.checkMouse(pos);
	};
	void mouseDragged(glm::vec2 pos) override {
		u.checkMouse(pos);
	};

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
//		rotateX ((mouseDragY)/height * 180.0);
		rotateY ((mouseDragX)/width * 180.0);
		
		rotateX (u.pFloat["slider0"] * 180.0);
		rotateY (u.pFloat["slider1"] * 180.0);
		
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
	}


	void draw() override {
		easyX += (mouseX-easyX)/20.0;
		easyY += (mouseY-easyY)/20.0;
	//	fbo.begin();
	//	desenha();
	//	fbo.end();
	//
	//	fbo.draw();

	//	test.prepare();
		desenha();
		
		noCamera();
		glDepthFunc(GL_ALWAYS);
		glEnable(GL_DEPTH_TEST);

		u.draw();
	//	test.final();
	}
} myApp;
