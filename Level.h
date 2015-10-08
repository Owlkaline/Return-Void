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

#include "Enemy.h"

#define BUTTON_UP   0
#define BUTTON_DOWN 1

class Level 
{
    public:
        Level();
        void Tick(Enemy *enemy);
        void Level1(Enemy *enemy);        
        void setup();
        void randomSpawn(Enemy *enemy, int i);
    protected:      
        bool inLevel;
        int crntLevel;
};


#endif
