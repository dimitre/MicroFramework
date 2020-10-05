
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

void rect(float x1, float y1, float w, float h) {
	glBegin(GL_POLYGON);
		float x2 = x1 + w;
		float y2 = y1 + h;
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
	glEnd();
}


void mouseclick(int button,int state,int x,int y) {
	if (state == GLUT_DOWN) {
		if (button == GLUT_RIGHT_BUTTON) {
//			if (suave++%2==1) {
//				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//			} else {
//				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//			}
		}
	}
}

float map(float v, float i1, float i2, float o1, float o2) {
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

void fill(int r, int g, int b, int a = 255) {
	glColor4f(r/255.0f,g/255.0f,b/255.0f,a/255.0);
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


void reshape(int w, int h)
{
//	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glTranslatef(0.0, 0.0, -3.6);
}

void idle(void)
{
    glutPostRedisplay();
}
