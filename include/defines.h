#ifndef DEFINES
#define DEFINES

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <png.h>
#endif

// key states
#define BUTTON_UP             0
#define BUTTON_DOWN           1

// Game States
#define MAINMENU              0
#define GAME                  1

#define SPACE_X_RESOLUTION    1920//1440
#define SPACE_Y_RESOLUTION    1080//810

// Arrow Keys
#define LEFT_KEY              0
#define RIGHT_KEY             1
#define UP_KEY                2
#define DOWN_KEY              3


// Keys
#define ESC                   27
#define A                     65
#define D                     68
#define S                     83
#define W                     87
#define a                     97
#define d                     100
#define s                     115
#define w                     119

#endif
