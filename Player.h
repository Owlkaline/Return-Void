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

#include "Bullet.h"

class Player 
{
    public:
        Player();
        void setup(GLuint *newTextures);
        void destroy();
        void respawn(int x, int y);
        
        void takeHealth(int Health);
        
        void Tick();
        void draw();  
        void fire();
        
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();

        void leftImage();
        void rightImage();
        void stationaryImage();
        
        float getX();
        float getY();
        int getHealth();
        int getWidth();
        int getHeight();
        bool getVisible();
         
        bool getBulletVisible(int i);
        float getBulletX(int i);
        float getBulletY(int i); 
        int getBulletWidth(int i); 
        int getBulletHeight(int i);     
        
        
        void setBulletVisible(bool visible, int i);

    protected:  
        int boundryX, boundryY; 
        int width, height;
        float x, y; 
        bool visible; 
        int health;
        Bullet bullets[10];
        GLuint texture;
        GLuint PlayerLeftText;
        GLuint PlayerRightText;
        GLuint PlayerText;
};


#endif
