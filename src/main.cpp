//Version 0.1

#include "../include/defines.h"

#include <time.h>  /* time */
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <iostream>

#include "../include/Menus/Shop.h"
#include "../include/Menus/MainMenu.h"
#include "../include/Menus/SettingsMenu.h"

#include "../include/GameTypes/Game.h"
#include "../include/GameTypes/Menu.h"

#include "../include/Namespaces/File.h"
#include "../include/Namespaces/LoadTexture.h"

int screenResX;
int screenResY;

int type = MAINMENU;

int refreshMillis = 20;

//Screen grid 100x100
double gridWidth = 100; //veiwing world x
double gridHeight = 100; // veiwing world y

//Aspect ratio of screen resolution
float aspectRatio;

//Scaled aspect Ratios, for the width and height
float aspectW;
float aspectH;

//Current coords of the mouse
float mouseX, mouseY;

//Unused currently, For setting game into gamemode when fullscreen
bool gameMode;

//Keeps the current key state, keeps the key state of the previous key state
unsigned int  specialKey[5];
unsigned int  mouseBtnState[3];
unsigned int  prevSpeicalKey[5];
unsigned int  prevMouseBtnState[3];

unsigned char keyState[255];
unsigned char prevKeyState[255];

GLuint mouseTexture;

DisplayManager* Display[4] = { new MainMenu(), new Game(), new SettingsMenu(), new Shop() };

//Sets the pace of the game
void Timer(int value) {
   glutPostRedisplay();  // Post a paint request to activate display()
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

  if( key == GLUT_KEY_LEFT) {
    specialKey[LEFT_KEY] = BUTTON_DOWN;
  } else {
    specialKey[LEFT_KEY] = BUTTON_UP;
  }

  if( key == GLUT_KEY_RIGHT) {
    specialKey[RIGHT_KEY] = BUTTON_DOWN;
  } else {
    specialKey[RIGHT_KEY] = BUTTON_UP;
  }

  if( key == GLUT_KEY_UP) {
    specialKey[UP_KEY] = BUTTON_DOWN;
  } else {
    specialKey[UP_KEY] = BUTTON_UP;
  }

  if( key == GLUT_KEY_DOWN) {
    specialKey[DOWN_KEY] = BUTTON_DOWN;
  } else {
    specialKey[DOWN_KEY] = BUTTON_UP;
  }

}

void mouseBtn(int btn, int state, int x, int y) {
  if(state == BUTTON_DOWN) {
    state = BUTTON_UP;
  } else {
    state = BUTTON_DOWN;
  }

  mouseBtnState[btn] = state;
}

//Updates mouse coords
void mouse(int x, int y) {
  mouseX = ((float)x);
  mouseY = SPACE_Y_RESOLUTION - ((float)y); 
}

void drawCursor() {
  if(type != GAME) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mouseTexture);
    // Nice blue #1e00d5
    glColor3f(0.117647059f, 0, 0.835294197f);

    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(mouseX-20, mouseY+20, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(mouseX+20, mouseY+20, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(mouseX+20, mouseY-20, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(mouseX-20, mouseY-20, 0.0);
    glEnd();

    glColor3f(1.0, 1.0, 1.0f);
    glDisable(GL_TEXTURE_2D);
  }
}

//Draw function
void display() {
  glClearColor(0.0f, 0.0f, 0.0f, 255.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Wipes screen clear

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//Blends colours with alpha

  //Texture options
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glColor4ub(255,255,255,255); //sets full colours and alpha

  Display[type]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState, keyState, prevKeyState);
  Display[type]->draw();
  
  drawCursor();
  
  if(Display[type]->hasEnded()) {
    int newtype = Display[type]->getEndType();
    switch(newtype) {
      case EXIT:
        glutLeaveGameMode();
        exit(0);
        break;
      case SEEDEDGAME:
        newtype = GAME;
        Display[newtype]->setSeed(time(NULL));
        break;
      case GAME:
        Display[newtype]->setSeed(567894);
        //Display[newtype]->setSeed(time(NULL));
        break;
    }
    Display[type]->clean();
    type = newtype;
    Display[type]->setup();
  }

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  prevKeyState[ESC] = keyState[ESC];
  prevMouseBtnState[GLUT_LEFT_BUTTON] = mouseBtnState[GLUT_LEFT_BUTTON];

  glEnable (GL_BLEND);
  glBlendFunc (GL_ONE, GL_ONE);

  glutSwapBuffers();
}

void setup() {
  int const screenResX = glutGet(GLUT_SCREEN_WIDTH);
  int const screenResY = glutGet(GLUT_SCREEN_HEIGHT);
  aspectRatio = (float)screenResX / screenResY;
  aspectW = SPACE_X_RESOLUTION/screenResX;
  aspectH = SPACE_Y_RESOLUTION/screenResY;

  for(int i = 0; i < 5; ++i) {
    specialKey[i] = BUTTON_UP;
  }
  mouseTexture = txt::LoadTexture("Textures/Game/Crosshair.png");
  Display[type]->setup();
}

int main(int argc, char** argv) {

  glClearColor(0.0f, 0.0f, 0.0f, 255.0f);     // black background

  glClearColor(0.0, 0.0, 0.0, 255.0);     // black background

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  gameMode = GAME_MODE_POSSIBLE;

  char mode_string[24];

  sprintf(mode_string, "%dx%d:32@60", glutGet(GLUT_SCREEN_WIDTH),
  glutGet(GLUT_SCREEN_HEIGHT));
  glutGameModeString(mode_string);

  if(GAME_MODE_POSSIBLE && !glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
    printf("GameMode %s is possible\n", mode_string);

    //destroys the current graphics window
    glutDestroyWindow(0);
    glutEnterGameMode();
  } else {
    printf("GameMode %s NOT possible\n", mode_string);

   // glutInitWindowPosition(100,100);
	//glutInitWindowSize(1280,720);

	glutCreateWindow("Return-Void");
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

  screenResX = glutGet(GLUT_SCREEN_WIDTH);
  screenResY = glutGet(GLUT_SCREEN_HEIGHT);

  const float ratio(static_cast<float>(SPACE_X_RESOLUTION)/static_cast<float>(SPACE_Y_RESOLUTION));

  gluOrtho2D(0.f, SPACE_X_RESOLUTION, 0.f, SPACE_Y_RESOLUTION);

  if (static_cast<float>(screenResX)/screenResY > ratio) {
    //  scale_ = static_cast<float>(screenResY)/SPACE_Y_RESOLUTION;
    screenResY = screenResY;
    screenResX  = screenResY * ratio;
    glViewport((screenResX-screenResX)*0.5f, 0, screenResX, screenResY);
  }
  else {
    // scale_ = static_cast<float>(screenResX)/SPACE_X_RESOLUTION;
    screenResY = screenResX / ratio;
    screenResX  = screenResX;
    glViewport(0, (screenResY-screenResY)*0.5f, screenResX, screenResY);
  }

  glClearColor(0.0, 0.0, 0.0, 255.0);

  printf("Setup Complete\n");

  glutMainLoop();
  return 0;
}
