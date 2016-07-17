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

#define BUTTONWIDTH            247
#define BUTTONHEIGHT           95
#define ARROWWIDTH             59

// Game States
#define EXIT                   -1
#define SEEDEDGAME             -2
#define MAINMENU               0
#define GAME                   1
#define SETTINGS               2
#define SHOP                   3

#define MINIMUM_DISTANCETOSHIP 100

// Ship Types
#define FIGHTERSHIP            1
#define GALACTICSHIP           2

// Powerups
#define NUMOFDROPS             3
#define NOTHING                0
#define COIN                   1
#define HEALTH                 2
#define SHIELD                 3

// Types of Bullets
#define REDPLASMA              1
#define BLUEPLASMA             2
#define GREENPLASMA            3
#define PURPLEPLASMA           4
#define SPIRAL                 5
#define ALPHAONEPLASMA         6

#define DAMAGETIMER            5

// Bullet timer
#define REDPLASMATIMER         20
#define BLUEPLASMATIMER        25
#define GREENPLASMATIMER       20
#define PURPLEPLASMATIMER      7
#define SPIRALTIMER            64
#define ALPHAONETIMER          180
 
// Types of Movement
#define FALL                   0
#define SINWAVE                1
#define SEMICIRCLE             2
#define LEFTSIDEFALL           3
#define RIGHTSIDEFALL          4
#define ALPHAONE               5

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
