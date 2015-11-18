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
        void Tick(float X, float Y);
        float getX();
        float getY();
        int getWidth();
        int getHeight();
        void setVisible(bool visible);
        bool getVisible();
        void fire(float newX, float newY, float mSpeed);
        void fire(float newX, float newY, float mSpeed, float X, float Y, bool pos);
        void draw();
        void setup(GLuint newText, float Width, float Height, float aspectRatio);
    protected:  
        float aspectRatio, angle;
        bool visible, pos;
        int boundryX, boundryY; 
        float width, height;
        float x, y, speed, startX, startY, endX, endY, distance, directionX, directionY;  
        GLuint texture; 
};


#endif
