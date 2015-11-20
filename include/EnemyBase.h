#ifndef ENEMYBASE_H
#define ENEMYBASE_H

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

class EnemyBase 
{
    public:
        EnemyBase();
        void setup(GLuint *Texture, GLuint *EnemyBuletTextures, float aspectRatio);
        void destroy();
        
        void Tick(float Px, float Py, bool Pvisible);
        void spawn(float x, float y, float speed, int maxHealth, float fireRate);
        
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
        
        void setX(float x);
        void setY(float y);
        void setSize(float size);
        void setSize(float width, float height);
        void setSpeed(float speed);
        void setMaxHealth(int maxHealth);
        void setVisible(bool visible);   
        void setFireRate(float rate);   
        void setBulletVisible(bool visible);      
    protected:  
        void move();
        int boundryX, boundryY; 
        float width, height;
        float x, y, targetX, targetY;
        float fireRate, speed, aspectRatio;  
        int health, maxHealth, hitTimer, score;
        bool visible, isHit;
        int shootTimer;
        Bullet bullets;
        GLuint texture;
};

#endif
