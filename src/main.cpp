//Version 0.1

#include "../include/defines.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>  /* time */
#include <iostream>
#include <fstream>

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#endif

#include "../include/Namespaces/File.h"
#include "../include/GameTypes/Game.h"
#include "../include/GameTypes/MainMenu.h"
#include "../include/GameTypes/SettingsMenu.h"

int screenResX;
int screenResY;

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
unsigned int  prevMouseBtnState[3];
unsigned int  specialKey[5];
unsigned int  prevSpeicalKey[5];

//Current coords of the mouse
float mouseX, mouseY;

int type = MAINMENU;

bool gameMode;

DisplayManager* Display[3] = { new MainMenu(), new Game(), new SettingsMenu() };

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
  mouseX = ((float)x); //* aspectW;
  mouseY = SPACE_Y_RESOLUTION - ((float)y); //* aspectH)) ; // Inverted: SPACE_Y_RESOLUTION - ((((float)y) * aspectH))
}

void saveGame() {
  std::ofstream ofs("./data/settings.bin", std::ios::binary);
  File::SaveFloat(ofs, VERSION);

  File::SaveBool(ofs, gameMode);
  File::SaveInt(ofs, 67);
  ofs.close();
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

  if(Display[type]->hasEnded()) {
    int newtype = Display[type]->getEndType();
    switch(newtype) {
      case EXIT:
        saveGame();
        glutLeaveGameMode();
        exit(0);
        break;
      case SEEDEDGAME:
        newtype = GAME;
        Display[newtype]->setSeed(567894);
        break;
      case GAME:
        Display[newtype]->setSeed(time(NULL));
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
  
  //Display[MAINMENU] = new MainMenu();
  Display[type]->setup();
}

int main(int argc, char** argv) {
  /* initialize random seed: */
 // srand (time(NULL));

  glClearColor(0.0f, 0.0f, 0.0f, 255.0f);     // black background

  glClearColor(0.0, 0.0, 0.0, 255.0);     // black background

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
  gameMode = GAME_MODE_POSSIBLE;
  if(File::check_if_file_exists("data/settings.bin")) {
    printf("Loading Settings...\n");
    std::ifstream ifs("./data/settings.bin", std::ios::binary);
    float version = File::LoadFloat(ifs);
    
    if(version == (float)VERSION) {
      gameMode = File::LoadBool(ifs);
     // int a = File::LoadInt(ifs1);
      //printf("%d\n", a);
    } else {
      printf("Incorrect settings verison\n version needed: %f\n", version);
      gameMode = GAME_MODE_POSSIBLE;
    }
    ifs.close(); 
  } else {
    printf("Creating settings file\n");
    std::ofstream ofs("./data/settings.bin", std::ios::binary);
  }
  
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
