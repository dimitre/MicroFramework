#define GL_SILENCE_DEPRECATION 1

#include <stdlib.h>
//#include <stdio.h>
#include <math.h>       /* fmod */

#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <map>
#include <vector>


#include <glm/vec2.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi




#define SKETCH "program.h"
//#define SKETCH "novelo.h"



#define PI 3.141592654

#define WIDTH 800
#define HEIGHT 800
int width = WIDTH;
int height = HEIGHT;

using namespace std;
//GLubyte checkImage[800][800][4];

int fullscreen=0;
//virtual void mousedrag (int x, int y) {}

#include "_basic.h"
#include "_util.h"

//#define RTMIDI17_COREAUDIO 1
//#include <rtmidi17/rtmidi17.hpp>
//#include "_midi.h"

//#include "_shader.h"
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
//	setup();
}


void display(void) {
	// start drawing
	glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

	glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE_ARB);
//	glEnable(GL_MULTISAMPLE);
//
	draw();
	
	glutSwapBuffers();
	glutPostRedisplay();
//	glFlush();

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
	if (key == 27) {
		exit(0);
	}
	else if (key == '-') {
		toggle_fullscreen();
	}
	else if (key == 's') {
//		useShader ^= 1;
	}
//    std::cout << "keydown " << key << "\n";
}

void keyUp (unsigned char key, int x, int y)
{
//    std::cout << "keyup " << key << "\n";
}



void timer( int value )
{
    glutTimerFunc( 16, timer, 0 );
    glutPostRedisplay();
}

bool setupIsDone = false;
int main(int argc, char** argv)
{
	
	if (!setupIsDone) {
		setup();
		setupIsDone = true;
	}
	
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
	
	
//	setupShader();
	
	init();
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);

    glutIdleFunc(idle);
	
	
    glutMouseFunc(mouseclick);
    glutMotionFunc(mousedrag);
    glutPassiveMotionFunc(mousemove);
	
	//setupLight();
	
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	
    glutTimerFunc( 0, timer, 0 );

    glutDisplayFunc(display);

    glutMainLoop();
	return 0;
//    return EXIT_SUCCESS;
}
