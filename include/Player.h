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
#include <vector>

#include "Bullet.h"

class Player
{
    public:
        Player();
        void setup(GLuint *newTextures, float aspectRatio);
        void destroy();
        void respawn(int x, int y);

        void takeHealth();

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
        float getWidth();
        float getHeight();
        float getX();
        float getY();
        bool isAlive();
        bool getVisible();
        bool getInvincible();

        int getBulletNum();
        int getBulletWidth(int i);
        int getBulletHeight(int i);
        float getBulletX(int i);
        float getBulletY(int i);
        bool getBulletVisible(int i);

        void setHealth(int newHealth);
        void setVisible(bool Visible);
        void setBulletVisible(bool visible, int i);

    protected:
        void flash();

        int health;
        int fireRate;
        float angle;
        float width, height;
        int boundryX, boundryY;
        int invincTimer, flashTimer;
        float aspectRatio, lastMouseX, lastMouseY;
        float directionX, directionY;

        float x, y;
        float speed;
        bool visible, alive, invincible;
        bool drawInvincible;
        std::vector<Bullet*> bullets;
        GLuint texture;
        GLuint bulletTexture;
        GLuint PlayerLeftText;
        GLuint PlayerRightText;
        GLuint PlayerText;

        void drawShip();
};


#endif
