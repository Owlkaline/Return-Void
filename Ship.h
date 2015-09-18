#ifndef SHIP_H
#define SHIP_H

#ifdef __APPLE__
#include <OpenGL/gl.h>// Header File For The OpenGL32 Library
#include <OpenGL/glu.h>// Header File For The GLu32 Library
#include <GLUT/glut.h>// Header File For The GLut Library
#else
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif

class Ship 
{
    public:
        Ship();
        int getHealth();
        float getX();
        float getY();
        void reset();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void draw();
    protected:  
        int boundryX, boundryY; 
        int width, height;
        float x, y;  
        int health; 
};


#endif
