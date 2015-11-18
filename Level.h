#ifndef LEVEL_H
#define LEVEL_H

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
#include <vector>

#include "Enemy.h"

#define BUTTON_UP   0
#define BUTTON_DOWN 1

class Level 
{
    public:
        Level();
        std::vector<Enemy*> Tick();
        void Level1();        
        void setup(GLuint *enemyTextures, float aspectRatio);
        void randomSpawn();
        void destroy();
    protected:      
        std::vector<Enemy*> enemy;
        GLuint enemyTexture[2];
        bool inLevel;
        float aspectRatio;
        int crntLevel;
};


#endif
