//Version 0.1

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
#include <iostream>

#include "Game.h"
#include "Menu.h"

#define BUTTON_UP   0
#define BUTTON_DOWN 1

enum Screen {
    sMenu = 0,
    sGame = 1,
    sOptions = 2  
};

double windowWidth = 100; //veiwing world x
double windowHeight = 100; // veiwing world y

double screenResX;
double screenResY;

int refreshMillis = 20; 
double gridSquareWidth; 

unsigned char keyState[255];
unsigned char prevKeyState[255];

//std::string yes;

Game game;
Menu menu;
Screen screen;

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

void drawChar(int PosX, int PosY, float R, float G, float B, char str[25], int length) {
    glColor3f(R, G, B); // Text Colour
    glRasterPos2i(PosX, PosY); //coordinates of text
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //colour blue
    
    void * font = GLUT_BITMAP_HELVETICA_18;//set font http://www.opengl.org/documentation/specs/glut/spec3/node76.html#SECTION000111000000000000000
       
     for(int i = 0; i < length; i++) {
             glutBitmapCharacter(font, str[i]);
     }  
     glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glColor4ub(255,255,255,255);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int screenNum;
    bool alive;
    switch(screen) {
       case sGame:
           if(keyState[27] == BUTTON_DOWN) //ESC
               screen = sMenu;
           alive = game.Tick(keyState, prevKeyState);
           if(!alive)
               screen = sMenu;
           break;
       case sMenu:           
           
           screenNum = menu.keyPress(keyState, prevKeyState);
           if(keyState[27] == BUTTON_DOWN) {//ESC
               if(prevKeyState[27] != BUTTON_DOWN) {
                   glutLeaveGameMode();
                   exit(0);
               }
           }
           
           switch(screenNum) {
               case -1:
                   exit(0);                  
                   break;
               case 1: 
                   screen = sGame;
                   game.setup();
                   break;
               case 2:
                   screen = sOptions;
                   break;
              
           }
           menu.draw();
           break;
       case sOptions:
           if(keyState[27] == BUTTON_DOWN) {//ESC
               screen = sMenu;
           }
           break;
    }
    keyState[27] = prevKeyState[27];
    drawChar(0, 98, 0.5f, 0.0f, 1.0f, "Version_0.1", 11);
    glFlush();       
    glutSwapBuffers(); 
}

void setup() {
    screenResX = glutGet(GLUT_SCREEN_WIDTH);
    screenResY = glutGet(GLUT_SCREEN_HEIGHT);

    printf("Screen Resolution: %f\n", screenResX);
    printf("Screen Resolution: %f\n", screenResY);
    
    screen = sMenu;    

    menu.setup();
}

int main(int argc, char** argv) {
	/* initialize random seed: */
    srand (time(NULL));
    
    time_t crntTime = time(0);
    printf("%li", crntTime);
    
    glClearColor(0.0f, 0.0f, 0.0f, 255.0f);         // black background

    glClearColor(0.0, 0.0, 0.0, 255.0);         // black background

	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    char mode_string[24];
 
    sprintf(mode_string, "%dx%d:32@60", glutGet(GLUT_SCREEN_WIDTH),
    glutGet(GLUT_SCREEN_HEIGHT));
    glutGameModeString(mode_string);
    if(glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
        printf("GameMode %s is possible\n", mode_string);
                                 // destroys the current graphics window
        glutDestroyWindow(0);
        glutEnterGameMode();
                                 // hide the cursor
        glutSetCursor(GLUT_CURSOR_NONE);
    } else {
        printf("GameMode %s NOT possible\n", mode_string);
        glutFullScreen();
    }
    glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_ALPHA_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutIgnoreKeyRepeat(1);
    
    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);   
    glutKeyboardFunc(keyboard); 
    glutKeyboardUpFunc(keyboard_up); 
    glutSpecialFunc(specialKeys);
    
    glOrtho(0.0, windowWidth, 0.0, windowHeight, -1.0, 1.0);   // setup a 100x100x2 viewing world
    glClearColor(0.0, 0.0, 0.0, 255.0);
    setup();
    printf("Setup Complete\n");
     
    glutMainLoop(); 
    return 0;
}
