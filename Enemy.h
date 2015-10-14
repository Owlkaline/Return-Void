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
        
        void Tick(float Px, float Py, bool Pvisible);
        
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
        void draw();
        void drawBullets();
        
        int looseHealth(int healthlost);
        
        void setX(float X);
        void setY(float Y);
        void setSize(float multiple);
        void setSpeed(float mSpeed);
        void setMaxHealth(int mHealth);
        void setVisible(bool visible);   
        void setFireRate(float rate);   
        void setBulletVisible(bool visible);      
    protected:  
        int boundryX, boundryY; 
        int width, height;
        float x, y, targetX, targetY, rate, speed;  
        int health, maxHealth;
        bool visible;
        Bullet bullets;
        GLuint texture;
};


#endif
