#ifndef PLAYER_H
#define PLAYER_H

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

class Player 
{
    public:
        Player();
        void setup(GLuint *newTextures, float aspectRatio);
        void destroy();
        void respawn(int x, int y);
        
        void takeHealth(int Health);
        
        void Tick(float mouseX, float mouseY);
        void draw();  
        void fire();
        
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        
        void rotateRight();
        void rotateLeft();

        void leftImage();
        void rightImage();
        void stationaryImage();
        
        int getHealth();
        int getWidth();
        int getHeight();
        float getX();
        float getY();
        bool isAlive();
        bool getVisible();
        bool getInvincible();
         
        int getBulletWidth(int i); 
        int getBulletHeight(int i);
        float getBulletX(int i);
        float getBulletY(int i); 
        bool getBulletVisible(int i);    
        
        void setHealth(int newHealth);
        void setVisible(bool Visible);
        void setBulletVisible(bool visible, int i);

    protected:  
        int health;
        int fireRate;
        float angle;
        float width, height;
        int boundryX, boundryY; 
        int increment;
        float aspectRatio;

        float x, y; 
        float speed;
        bool visible, alive, invincible;
        clock_t invincibleTime;
        clock_t globalTime; 
        clock_t drawTime;
        bool drawInvincible;
        Bullet bullets[10];
        GLuint texture;
        GLuint PlayerLeftText;
        GLuint PlayerRightText;
        GLuint PlayerText;
        
        void drawShip();
};


#endif
