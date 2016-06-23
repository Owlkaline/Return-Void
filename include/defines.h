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

#define VERSION                1.2

#define GAME_MODE_POSSIBLE     0

// Game x, y coordinate system
#define SPACE_X_RESOLUTION     1920 //1440
#define SPACE_Y_RESOLUTION     1080 //810

// key states
#define BUTTON_UP              0
#define BUTTON_DOWN            1

// Game States
#define EXIT                   -1
#define SEEDEDGAME             -2
#define MAINMENU               0
#define GAME                   1
#define SETTINGS               2

#define MINIMUM_DISTANCETOSHIP 100

// Powerups
#define NUMOFDROPS             3
#define NOTHING                0
#define COIN                   1
#define HEALTH                 2
#define SHIELD                 3

// Types of Bullets
#define REDPLASMA              1
#define BLUEPLASMA             2

#define DRAWQUADTREE           0
#define DRAWHITBOX             0

// Arrow Keys
#define LEFT_KEY               0
#define RIGHT_KEY              1
#define UP_KEY                 2
#define DOWN_KEY               3

// Keys
#define ESC                    27

#endif
