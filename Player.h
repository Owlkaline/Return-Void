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
        void reset();
        
        void fire();
        void moveLeft();
        void moveRight();
        void moveUp();
        void moveDown();
        void draw();  
        
        float getX();
        float getY();
        int getHealth();
        int getWidth();
        int getHeight(); 
        bool getBulletVisible(int i);
        float getBulletX(int i);
        float getBulletY(int i); 
        int getBulletWidth(int i); 
        int getBulletHeight(int i);     
        
        void setBulletVisible(bool visible, int i);
      
        void leftImage();
        void rightImage();
        void stationaryImage();

    protected:  
        int boundryX, boundryY; 
        int width, height;
        float x, y;  
        int health;
        Bullet bullets[20];
        GLuint texture;
        GLuint PlayerLeftText;
        GLuint PlayerRightText;
        GLuint PlayerText;
};


#endif