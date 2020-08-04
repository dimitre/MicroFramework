#define SKETCH "program.h"
//#define SKETCH "novelo.h"

#define GL_SILENCE_DEPRECATION 1

#define PI 3.141592654


#include <stdlib.h>
//#include <stdio.h>
#include <math.h>       /* fmod */
#include <GLUT/glut.h>
#include <iostream>

#define WIDTH 800;
#define HEIGHT 800;
int width = 800;
int height = 800;

using namespace std;

static GLuint texName;
GLubyte checkImage[800][800][4];

int i, j;
//int width=64*20;
//int height=64*20;
int fullscreen=0;
int clip, suave;
float raio=1.5;
float raio_tex;


//virtual void mousedrag (int x, int y) {} 

void makeTex(void) {
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);    
	glGenTextures(1, &texName);    
	glBindTexture(GL_TEXTURE_2D, texName);    
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);    
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); 
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);    
	
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,                     GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,                     GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,                     GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,                     GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage); 
	
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);    
	
	glBindTexture(GL_TEXTURE_2D, texName);  
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
			if (suave++%2==1) {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			} else {
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			}
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
//	glColor3f(r/255.0f,g/255.0f,b/255.0f);
}

void stroke(int r, int g, int b, int a=255) {
	glColor3f(r/255.0f,g/255.0f,b/255.0f);
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

void translate(float x, float y, float z = 0) {
	glTranslatef(x, y, z);
}

void idle(void)
{
    glutPostRedisplay();
}

void readTex() {
	glReadBuffer(GL_FRONT);
	glReadPixels(0,0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkImage);
}

#include "_shader.h"
#include "_util.h"

#include SKETCH

void init(void) {
	glClearColor (0.0, 0.0, 0.0, 0.0);
	//glShadeModel(GL_FLAT);
	//glEnable(GL_DEPTH_TEST);
	//glClearColor( 0.0, 0.0, 0.0, 0.0 );
	// enable polygon antialiasing
	//glBlendFunc( GL_SRC_ALPHA_SATURATE, GL_ONE );
	glEnable( GL_BLEND );
	glEnable( GL_POLYGON_SMOOTH );
	glDisable( GL_DEPTH_TEST );
	setup();
}


void display(void) {
	// start drawing
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

	glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE_ARB);
//	glEnable(GL_MULTISAMPLE);

//

	
	
	draw();
	
	glutPostRedisplay();
	glFlush();

}

bool is_fullscreen = false;
void toggle_fullscreen() {
  if (is_fullscreen) {
    glutReshapeWindow(width, height);
    glutPositionWindow(50, 50);
//    printf("%d, %d\n", pos_x, pos_y);
  } else {
    glutFullScreen();
  }
  is_fullscreen = !is_fullscreen;
}

void keyDown (unsigned char key, int x, int y)
{
	if (key == 's') {
		useShader ^= 1;
	}
	if (key == '-') {
		toggle_fullscreen();
	}
//    std::cout << "keydown " << key << "\n";
}

void keyUp (unsigned char key, int x, int y)
{
//    std::cout << "keyup " << key << "\n";
}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
	
    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
//	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
//	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    
//    glutInitWindowPosition(100,100);
	glutInitWindowSize(width, height);
    if (fullscreen) {
        char mode[1000];
        //sprintf(mode,"%dx%d:32@72",width, height);
        glutGameModeString(mode);
		
        glutEnterGameMode();
    } else {
		//glutInitWindowPosition(100, 100);
	    glutCreateWindow("Dmtr.org MicroFramework");
	}
	
	
	setupShader();
	
	init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
	
	
    glutMouseFunc(mouseclick);
    glutMotionFunc(mousedrag);
    glutPassiveMotionFunc(mousemove);
	
	//setupLight();
	
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop();
    return EXIT_SUCCESS;
}

