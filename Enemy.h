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
#include <time.h>

#include "Bullet.h"

class Enemy 
{
    public:
        Enemy();
        void setup(GLuint *Texture);
        void destroy();
        
        float getX();
        float getY();
        int getWidth();
        int getHeight();        
        int getHealth();
        bool getVisible();
        bool getBulletVisible(); 
        float getBulletX(); 
        float getBulletY(); 
        float getBulletWidth(); 
        float getBulletHeight(); 
        
        void fire(int Px, int Py);
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void draw(int Px, int Py);
        
        int looseHealth(int healthlost);
        
        void setVisible(bool visible);      
        void setBulletVisible(bool visible);      
    protected:  
        int boundryX, boundryY; 
        int width, height;
        float x, y, targetX, targetY;  
        int health;
        bool isVisible;
        Bullet bullets;
        GLuint texture;
};


#endif
