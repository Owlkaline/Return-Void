#ifndef BULLET_H
#define BULLET_H

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

class Bullet
{
    public:
        Bullet();
        float getX();
        float getY();
        int getWidth();
        int getHeight();
        void setVisible(bool visible);
        bool getVisible();
        void fire(float newX, float newY, float mSpeed);
        void moveUp();
        void moveDown();
        void draw();
        void setup(GLuint newText);
    protected:  
        bool isVisible;
        int boundryX, boundryY; 
        int width, height;
        float x, y, speed;  
        GLuint texture; 
};


#endif
