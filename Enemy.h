#ifndef ENEMY_H
#define ENEMY_H

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

#include "Bullet.h"

class Enemy 
{
    public:
        Enemy();
        int getHealth();
        void looseHealth(int healthlost);
        float getX();
        float getY();
        int getWidth();
        int getHeight();
        void setVisible(bool visible);
        bool getVisible();
        void setBulletVisible(bool visible);
        void fire();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void draw();
        void setup(GLuint newText, GLuint bulletText);
    protected:  
        int boundryX, boundryY; 
        int width, height;
        float x, y;  
        int health;
        bool isVisible;
        Bullet bullets;
        GLuint texture;
};


#endif
