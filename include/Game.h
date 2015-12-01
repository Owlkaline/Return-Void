#ifndef GAME_H
#define GAME_H

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <png.h>
#endif

#include <iostream>
#include <list>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <fstream>
#include <vector>

#include "Player.h"
#include "EnemyTypes.h"
#include "Level.h"

#define BUTTON_UP   0
#define BUTTON_DOWN 1

class Game
{
    public:
        Game();
        void setup(float aspectRatio);
        void destroy();
        bool Tick(unsigned char* keyState, unsigned char* prevKeyState, float mouseX, float mouseY, unsigned int* mouseBtnState);
        void collisions();
        void draw();
        void drawGameOver();
    protected:
        Player player;
        std::vector<BaseEnemy*> enemy;
        Level level;
        clock_t crntTime;
        clock_t shootTime;
        clock_t playerTime;
        int increment;
        int score;

        bool showHitBox;
        bool collisionOff;

        void safeSpawn();

        void keyPress(unsigned char* keyState, unsigned char* prevKeyState,  unsigned int* mouseBtnState);

        void drawHitBox(float Ax, float Ay, float Aw, float Ah);
        void drawScore();
        void drawStars();
        void drawChar(int PosX, int PosY, float R, float G, float B, char str[25], int length);
        void drawHud();
        GLuint LoadTexture( const char * filename );
        GLuint texture[12];
        GLuint gameOverTexture;
};


#endif
