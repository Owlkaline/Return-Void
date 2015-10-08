#ifndef GAME_H
#define GAME_H

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif

#include <stdio.h> 
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "Player.h"
#include "Enemy.h"

#define BUTTON_UP   0
#define BUTTON_DOWN 1

class Game 
{
    public:
        Game();
        void setup();
        void destroy();
        
        void keyPress(unsigned char* keyState, unsigned char* prevKeyState);
        void draw();
        void collisions();        
    protected:  
        Player player;
        Enemy enemy;
        int score;
        void drawScore();
        void drawStars();
        float atan2(float opposite, float adjacent);
        void drawChar(int PosX, int PosY, float R, float G, float B, char str[25], int length);
        //void drawString(int PosX, int PosY, float R, float G, float B, std::string str);
        void drawHud();
        GLuint LoadTexture( const char * filename );
        GLuint texture[12];
};


#endif
