#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>      /* time */
#include <ctype.h>

#include "Ship.h"

#define BUTTON_UP   0
#define BUTTON_DOWN 1

double windowWidth = 100; //veiwing world x
double windowHeight = 100; // veiwing world y

double screenResX;
double screenResY;

int refreshMillis = 20;
double gridSquareWidth;

unsigned char keyState[255];

Ship ship;

void Timer(int value) {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

void keyboard(unsigned char key, int x, int y) {
        keyState[putchar (tolower(key))] = BUTTON_DOWN;
}

void keyboard_up(unsigned char key, int x, int y) {
        keyState[putchar (tolower(key))] = BUTTON_UP;        
}

void specialKeys(int key, int x, int y) {
     switch (key) { 
     case GLUT_KEY_LEFT:
            break; 
     }
}

void mouse(int button, int state, int x, int y) {
    
}

void display() {
    glClear( GL_COLOR_BUFFER_BIT);
    ship.draw();
    if(keyState[27] == BUTTON_DOWN)//ESC
        exit(0);
    if(keyState[(unsigned char)'a'] == BUTTON_DOWN)
        ship.moveLeft();
    if(keyState[(unsigned char)'d'] == BUTTON_DOWN)
        ship.moveRight();
    if(keyState[(unsigned char)'w'] == BUTTON_DOWN)
        ship.moveUp();
    if(keyState[(unsigned char)'s'] == BUTTON_DOWN)
        ship.moveDown();
        
           
    glutSwapBuffers(); 
}

void setup() {
    screenResX = glutGet(GLUT_SCREEN_WIDTH);
    screenResY = glutGet(GLUT_SCREEN_HEIGHT);

    printf("Screen Resolution: %f\n", screenResX);
    printf("Screen Resolution: %f\n", screenResY);


}

int main(int argc, char** argv) {
	/* initialize random seed: */
    srand (time(NULL));
    
    glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Faggot window"); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND ); 
    glutIgnoreKeyRepeat(1);
    glutFullScreen();
    
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);   
    glutKeyboardFunc(keyboard); 
    glutKeyboardUpFunc(keyboard_up); 
    glutSpecialFunc(specialKeys);
    
    //Ortho (x1,x2,y1,y2,z1,z2). 
    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);   // setup a 100x100x2 viewing world
    //glOrtho(0.0, glutGet(GLUT_SCREEN_WIDTH)/100, 0.0, glutGet(GLUT_SCREEN_HEIGHT)/100, -1.0, 1.0);   // setup a wxhx2 viewing world
  //  glClearColor(0.0, 0.0, 0.0, 1.0);
    setup();
    printf("Setup Complete\n");
    glutMainLoop(); 

    return 0;
}
