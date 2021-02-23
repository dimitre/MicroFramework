struct microApp {
public:
	float random(float min, float max) {
		return fmod(rand(), max) + min;
	//	return min + rand() * (max-min);
	}

	void push() {
		glPushMatrix();
	}

	void pop() {
		glPopMatrix();
	}

	void circle (float x, float y , float r) {
		GLUquadricObj* quadratic;
		quadratic = gluNewQuadric();
		gluQuadricNormals(quadratic, GLU_SMOOTH);
		push();
		glTranslatef(x, y, 0);
		gluDisk(quadratic,0,r,32,32);
		pop();
	}

	void box(float a) {
		glutWireCube(a);
	}


	// pointers?
	static void rect(float x1, float y1, float w, float h) {
	//	static void rect(float x1, float y1, float w, float h) {

	//void rect(float & x1, float & y1, float & w, float & h) {
		glBegin(GL_POLYGON);
			float x2 = x1 + w;
			float y2 = y1 + h;
			glVertex2f(x1, y1);
			glVertex2f(x2, y1);
			glVertex2f(x2, y2);
			glVertex2f(x1, y2);
		glEnd();
	}

	// todo: pointers
#ifdef USEGLM
	static void rect(glm::vec2 pos, glm::vec2 dimensions) {
		rect(pos.x, pos.y, dimensions.x, dimensions.y);
	}
#endif

	float remap(float v, float i1, float i2, float o1, float o2) {
		return ((v-i1)/(i2-i1)) * (o2-o1) + o1;
	}

	void lineWidth(float w) {
		glLineWidth(w);
	}

	void rotateX (float angle) {
		glRotatef (angle, 1.0f, 0, 0);
	}

	void rotateY (float angle) {
		glRotatef (angle, 0, 1, 0);
	}

	void rotateZ (float angle) {
		glRotatef (angle, 0, 0, 1);
	}


	struct color {
	public:
		float r, g, b, a = 255.0;
		color();
		color(string hexa) {
			// string redhexa = hexa.substr(1,2);
			unsigned int RGB;
			std::stringstream ss;
			ss << std::hex << hexa;
			ss >> RGB;
			if (hexa.size() == 6) {
				r = (RGB >> 16) & 0xFF;
				g = (RGB >> 8) & 0xFF;
				b = RGB & 0xFF;
			} else if (hexa.size() == 2) {
				r = g = b = RGB;
			}
		}
		color(int rr, int gg, int bb, int aa=255) : r(rr), g(gg), b(bb), a(aa) {
			
		}
	};

	void fill(int r, int g, int b, int a = 255) {
		glColor4f(r/255.0f,g/255.0f,b/255.0f,a/255.0);
	}

	void fill(color c) {
		glColor4f(c.r/255.0f,c.g/255.0f,c.b/255.0f,c.a/255.0);
	}

	void stroke(int r, int g, int b, int a=255) {
	//	glColor3f(r/255.0f,g/255.0f,b/255.0f);
		glColor4f(r/255.0f,g/255.0f,b/255.0f,a/255.0);
	}

	void line(float x1, float y1, float x2, float y2) {
		glBegin(GL_LINES);
			glVertex2f(x1,y1);
			glVertex2f(x2,y2);
		glEnd();
	}

	void fill(int cinza) {
		glColor3f(cinza/255.0f,cinza/255.0f,cinza/255.0f);
	}

	void camera(void)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(40.0, 1.0, .1, 2450); // ultimo parametro far plane
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0, 0, 450.0, 0, 0, 0, 0, 1, 0);
	}


	// teste. remover - testando em 2021
	void noCamera(void) {
		glViewport(0,0,800,800);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, 800, 800, 0.0, -1.0, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	//	glMatrixMode(GL_TEXTURE);
		
	}


	void background(float r, float g, float b) {
		glClearColor( r/255.0, g/255.0, b/255.0, 1.0 );
	}

	void background(float l) {
		glClearColor( l/255.0, l/255.0, l/255.0, 1.0 );
	}

	void clear() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void translate(float x, float y, float z = 0) {
		glTranslatef(x, y, z);
	}


#ifdef USEGLM
	friend class rectangle;

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
#endif

	virtual void setup() {}
	virtual void draw() {
		cout << "primitive draw" << endl;
	}

	virtual void mousemove(int x, int y) {}
	virtual void mousedrag(int x, int y) {}
#ifdef USEGLM
	virtual void mousePressed(glm::vec2 pos) {}
	virtual void mouseDragged(glm::vec2 pos) {}
#endif

};

// forward declaration
//struct app : public microApp;


#ifdef USEGLM
struct interface : public microApp {
public:
	map <string, float>		pFloat;
	map <string, bool>		pBool;
	
	struct element : public microApp {
	public:
		float * _val = NULL;
		rectangle rect = rectangle(glm::vec2(0,0), glm::vec2(200,20));
		rectangle rect2 = rectangle(glm::vec2(0,0), glm::vec2(200,20));
		glm::vec2 pos;
		// color cor = color(255,0,0);
		// color cor2 = color(0,0,255);
		color cor = color("33");
//		color cor2 = color("00ffaa");
		color cor2 = color("ff0077");
		
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
				float val = remap(mouse.x, rect.pos.x, rect.pos2.x, 0, 1);
				if (_val != NULL) {
					*_val = val;
				}
				rect2.dimensions.x = rect.dimensions.x * val;

//				cor = color(random(0,255), random(0,255), random(0,255));
			}
		}
	};

	element elements[10];
	//vector <element> elements;

	void setup() override {
		for (int a=0; a<10; a++) {
			int x = 20;
			int y = 20 + a*30;
			elements[a] = element(glm::vec2(x,y));
			string name = "slider" + to_string(a);
			elements[a]._val = &pFloat[name];
		}
	}

	void checkMouse(glm::vec2 mouse) {
		for (auto & e : elements) {
			e.checkMouse(glm::vec2(mouse));
		}
	}

	void draw() override {
		for (auto & e : elements) {
			e.draw();
		}
	}
};
#endif
