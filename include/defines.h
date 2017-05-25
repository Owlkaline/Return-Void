#ifndef DEFINES
#define DEFINES

#include <cstdlib>

#define VERSION                1.5

#define GAME_MODE_POSSIBLE     0

// Game x, y coordinate system
#define SPACE_X_RESOLUTION     1920 //1440
#define SPACE_Y_RESOLUTION     1080 //810

#define TEXTR                  0.5
#define TEXTG                  0.5
#define TEXTB                  1.0

// key states
#define BUTTON_UP              0
#define BUTTON_DOWN            1

#define BUTTONWIDTH            247
#define BUTTONHEIGHT           95
#define ARROWWIDTH             59

#define UP                     0
#define DOWN                   1

// Game States
#define EXIT                   -1
#define SEEDEDGAME             -2
#define MAINMENU               0
#define ENDLESSGAME            1
#define SETTINGS               2
#define SHOP                   3
#define HIGHSCORE              4
#define STORY                  5

#define MINIMUM_DISTANCETOSHIP 100

// Ship Types
#define FIGHTERSHIP            1
#define GALACTICSHIP           2
#define HEROSHIP3              3

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
#define DOTBULLET              7

#define DAMAGETIMER            5

// Bullet timer
#define REDPLASMATIMER         20
#define BLUEPLASMATIMER        25
#define GREENPLASMATIMER       70
#define PURPLEPLASMATIMER      7
#define SPIRALTIMER            64
#define ALPHAONETIMER          180
#define DOTBULLETTIMER         50
 
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
#define LEFT_KEY               263
#define RIGHT_KEY              262
#define UP_KEY                 265
#define DOWN_KEY               264

// Keys
#define ESC                    256
/*
inline void drawQuad(float x, float w, float y, float h, int rotation)
	{
		glBegin(GL_QUADS);
		  if(rotation == DOWN) {
		    glTexCoord2f(0.0, 0.0); glVertex3f( x-w/2,  y+h/2, 0.0);
			  glTexCoord2f(0.0, 1.0); glVertex3f( x-w/2,  y-h/2, 0.0);
			  glTexCoord2f(1.0, 1.0); glVertex3f( x+w/2,  y-h/2, 0.0);
			  glTexCoord2f(1.0, 0.0); glVertex3f( x+w/2,  y+h/2, 0.0);
			} else {
		    glTexCoord2f(1.0, 1.0); glVertex3f( x-w/2,  y+h/2, 0.0);
			  glTexCoord2f(1.0, 0.0); glVertex3f( x-w/2,  y-h/2, 0.0);
			  glTexCoord2f(0.0, 0.0); glVertex3f( x+w/2,  y-h/2, 0.0);
			  glTexCoord2f(0.0, 1.0); glVertex3f( x+w/2,  y+h/2, 0.0);			
			}
		glEnd();
	}
*/
#endif
