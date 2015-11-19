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
#include <math.h>

class Bullet
{
    public:
        Bullet();
        void Tick();
        float getX();
        float getY();
        int getWidth();
        int getHeight();
        void setVisible(bool visible);
        bool getVisible();
        void fire(float x, float y, float speed);
        void fire(float x, float y, float endX, float endY, float speed);
        void fire(float x, float y, float directionX, float directionY,  float speed, float angle);
        void draw();
        void setup(GLuint newText, float width, float height, float aspectRatio);
    protected:  
        float aspectRatio, angle;
        bool visible;
        int boundryX, boundryY; 
        float width, height;
        float x, y, speed, startX, startY, endX, endY, distance, directionX, directionY;  
        GLuint texture; 
};


#endif
