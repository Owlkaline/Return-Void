#include "Ship.h"

#include <stdlib.h>

#define NUMBULLETS 20

Ship::Ship() {
        width = 5;
        height = 10;
        x = 10.0f;
        y = 5.0f;  
        health = 5; 
        boundryX = 100 - width;
        boundryY = 100 - height;

        printf("Ship Constructed\n");
   }
   
void Ship::setup(GLuint shipTexture, GLuint leftTexture, GLuint rightTexture, GLuint bulletTexture) {
    
    shipText = shipTexture;
    ShipLeftText = leftTexture;
    ShipRightText = rightTexture;
    texture = shipTexture;
    
    for(int i = 0; i < NUMBULLETS; ++i) 
        bullets[i].setup(bulletTexture);
}

void Ship::leftImage() {
    texture = ShipLeftText;
}

void Ship::rightImage() {
    texture = ShipRightText;
}

void Ship::stationaryImage() {
    texture = shipText;
}

void Ship::draw() {
    //glColor3f(0.0, 1.0, 0.0);
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    if(x > boundryX)
        x = boundryX;
    if(y > boundryY)
        y = boundryY;

    glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(x, y + height, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x + width, y + height, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x + width, y, 0.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y, 0.0);
    glEnd();

  
    for(int i = 0; i < NUMBULLETS; ++i) {
        if(bullets[i].getVisible())
            bullets[i].draw();
    }
  glDisable(GL_TEXTURE_2D);
}

void Ship::fire() {
    bool found = false;
    for(int i = 0; i < NUMBULLETS; ++i) {
        if(bullets[i].getVisible() == false) {
            bullets[i].fire(x + width/2 - 0.5, y + height, 1.75);
            found = true;
        }
        if(found)
            break;
    }
}  
     
int Ship::getHealth() { return health; }
float Ship::getX() { return x; }
float Ship::getY() { return y; }
int Ship::getWidth() { return width; }
int Ship::getHeight() { return height; }
void Ship::setBulletVisible(bool visible, int i) { bullets[i].setVisible(visible); }
bool Ship::getBulletVisible(int i) { return bullets[i].getVisible(); }
float Ship::getBulletX(int i) { return bullets[i].getX(); }
float Ship::getBulletY(int i) { return bullets[i].getY(); }
int Ship::getBulletWidth(int i) { return bullets[i].getWidth(); }
int Ship::getBulletHeight(int i) { return bullets[i].getHeight(); }
void Ship::reset() { x = 10; y = 5; health--;}
void Ship::moveLeft() { x -= 0.5f; }
void Ship::moveRight() { x += 0.5f; }
void Ship::moveUp() { y += 0.25f; }
void Ship::moveDown() { y -= 0.25f; }
