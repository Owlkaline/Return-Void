//Version 0.1

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>      /* time */
#include <iostream>
#include <fstream>

#include "../include/Game.h"
#include "../include/Menu.h"

//key states
#define BUTTON_UP   0
#define BUTTON_DOWN 1

enum Screen {
    sGame,
    sMenu
};

//Textures
GLuint menuTextures[4];
GLuint gameTextures[19];

//Screen grid 100x100
double gridWidth = 100; //veiwing world x
double gridHeight = 100; // veiwing world y

//Aspect ratio of screen resolution
float aspectRatio;

//Scaled aspect Ratios, for the width and height
float aspectW;
float aspectH;

int refreshMillis = 20;

//Keeps the current key state, keeps the key state of the previous key state
unsigned char keyState[255];
unsigned char prevKeyState[255];
unsigned int  mouseBtnState[3];

//Current coords of the mouse
float mouseX, mouseY;

//is the Player alive?
bool alive;

//Game Menu and Screen objects
Game game;
Menu menu;
Screen screen;

//Sets the pace of the game
void Timer(int value) {
   glutPostRedisplay();    // Post a paint request to activate display()
   glutTimerFunc(refreshMillis, Timer, 0); // subsequent timer call at milliseconds
}

//Updates what keys are pressed
void keyboard(unsigned char key, int x, int y) {
    keyState[putchar (tolower(key))] = BUTTON_DOWN;
}

//Updates what keys are released
void keyboard_up(unsigned char key, int x, int y) {
        keyState[putchar (tolower(key))] = BUTTON_UP;
}

//keys for special key presses (F1, F2, CTRL, LEFT, RIGHT etc)
void specialKeys(int key, int x, int y) {
     switch (key) {
     case GLUT_KEY_LEFT:
            break;
     }
}

void mouseBtn(int btn, int state, int x, int y) {
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
        mouseBtnState[0] = BUTTON_DOWN;
    }

    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN) {
        mouseBtnState[1] = BUTTON_DOWN;
    }

    if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN) {
        mouseBtnState[2] = BUTTON_DOWN;
    }

    if(btn==GLUT_LEFT_BUTTON && state==GLUT_UP) {
        mouseBtnState[0] = BUTTON_UP;
    }

    if(btn==GLUT_RIGHT_BUTTON && state==GLUT_UP) {
        mouseBtnState[1] = BUTTON_UP;
    }

    if(btn==GLUT_MIDDLE_BUTTON && state==GLUT_UP) {
        mouseBtnState[2] = BUTTON_DOWN;
    }
}

//Updates mouse coords
void mouse(int x, int y) {
    mouseX = x * aspectW;
    mouseY = 100 - (y * aspectH);
}

//Draws Text to the screen
void drawChar(int PosX, int PosY, float R, float G, float B, char str[25], int length) {
    glColor3f(R, G, B); // Text Colour
    glRasterPos2i(PosX, PosY); //coordinates of text
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //colour blue

    void * font = GLUT_BITMAP_HELVETICA_18;//set font http://www.opengl.org/documentation/specs/glut/spec3/node76.html#SECTION000111000000000000000

     for(int i = 0; i < length; i++) {
             glutBitmapCharacter(font, str[i]);//Draw character to screen
     }
     glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//return colours to the full amounts
}

//Draw function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wipes screen clear

	glColor4ub(255,255,255,255); //sets full colours and alpha
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//Blends colours with alpha

	//Texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int screenNum; //keeps current screen number
    switch(screen) {
       case sGame:
           //Returns to the menu when escape is pressed
           if(keyState[27] == BUTTON_DOWN) {//ESC
               alive = true;
               game.destroy();
               screen = sMenu;
           }

           //Draws the game
           game.draw();

           //Checks to see if player is alive to show the game over screen
           if(!alive) {
               game.drawGameOver();
               if(keyState[(unsigned char)'y'] == BUTTON_DOWN) {//Restart Game
                   game.destroy();
                   game.setup(aspectRatio);
                   alive = true;
               } else  if(keyState[(unsigned char)'n'] == BUTTON_DOWN) {//Return to Menu
                   game.destroy();
                   screen = sMenu;
                   alive = true;
               }
           } else {
               //updates game
               alive = game.Tick(keyState, prevKeyState, mouseX, mouseY, mouseBtnState);
           }
           break;
       case sMenu:
           game.destroy();
           glutSetCursor(GLUT_CURSOR_NONE);
           screenNum = menu.keyPress(keyState, prevKeyState);

           switch(screenNum) {
               case 1:
                   screen = sGame;
                   game.setup(aspectRatio);
                   break;
           }
           menu.draw();
           break;
    }
    prevKeyState[27] = keyState[27];//esc
    prevKeyState[13] = keyState[13];//enter
    char versionStr[12] = "Version_0.4";
    drawChar(0, 98, 0.5f, 0.0f, 1.0f, versionStr, 12);
    glEnable (GL_BLEND);
    glBlendFunc (GL_ONE, GL_ONE);
   // glFlush();
    glutSwapBuffers();
}

void setup() {
    int const screenResX = glutGet(GLUT_SCREEN_WIDTH);
    int const screenResY = glutGet(GLUT_SCREEN_HEIGHT);
    aspectRatio = (float)screenResX / screenResY;
    aspectW = 100.0f/screenResX;
    aspectH = 100.0f/screenResY;
    screen = sMenu;
    alive = true;

    menu.setup();
}

int main(int argc, char** argv) {
	/* initialize random seed: */
    srand (time(NULL));

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
    } else {
        printf("GameMode %s NOT possible\n", mode_string);
        glutFullScreen();
    }
    // hide the cursor
    glutSetCursor(GLUT_CURSOR_NONE);

    glBlendFunc(GL_ONE_MINUS_DST_ALPHA,GL_DST_ALPHA);
    glAlphaFunc(GL_GREATER, 0.1);
    glEnable(GL_ALPHA_TEST);

    glutIgnoreKeyRepeat(1);

    glutDisplayFunc(display);
    glutTimerFunc(0, Timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouseBtn);
    glutMotionFunc(mouse);
    glutPassiveMotionFunc(mouse);
    setup();

    int const screenResX = glutGet(GLUT_SCREEN_WIDTH);
    int const screenResY = glutGet(GLUT_SCREEN_HEIGHT);


//    glOrtho(0.0, gridWidth, 0.0, gridHeight, -1.0, 1.0);   // setup a 100x100x2 viewing world
    glOrtho(0, (gridWidth/screenResX)*screenResX, 0, (gridHeight/screenResY)*screenResY, -1.0, 1.0);   // setup a 100x100x2 viewing world
   // glOrtho(-aspectRatio*100, aspectRatio*100, -1*100, 1*100, -1, 1);
    glClearColor(0.0, 0.0, 0.0, 255.0);

    printf("Setup Complete\n");

    glutMainLoop();
    return 0;
}
