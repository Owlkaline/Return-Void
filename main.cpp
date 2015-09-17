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
#include <time.h>       /* time */


double windowWidth;
double windowHeight;

int refreshMillis = 100;
double gridSquareWidth;
double gridSquareHeight;
int zoom = 20;

void Timer(int value) {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:  // ESC key
            exit(0);//exit
            break;
    }
}

void specialKeys(int key, int x, int y) {
    
}

void mouse(int button, int state, int x, int y) {
    
}

void display() {
    //Map.draw(gridSquareWidth, gridSquareHeight, zoom);   
    glutSwapBuffers(); 
}

void setup(){
    windowWidth = glutGet(GLUT_SCREEN_WIDTH);
    windowHeight = glutGet(GLUT_SCREEN_HEIGHT);
    
    gridSquareWidth = (2.0f / zoom);
    gridSquareHeight = 2.0f / zoom * (windowWidth/windowHeight);
    printf("Window Width: %f\n", windowWidth);
    printf("Window Height: %f\n", windowHeight);

    //Map.setup();
}

int main(int argc, char** argv) {
	/* initialize random seed: */
    srand (time(NULL));
    
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow("Faggot window"); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND ); 
    glutFullScreen();
    
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);   
    glutKeyboardFunc(keyboard); 
    glutSpecialFunc(specialKeys);
    
  //  glClearColor(0.0, 0.0, 0.0, 1.0);
    //setup();
    printf("Setup Complete\n");
    glutMainLoop(); 

    return 0;
}
