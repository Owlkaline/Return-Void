#include "Player.h"

#include <stdlib.h>

#define NUMBULLETS 20

Player::Player() {
        width = 5;
        height = 10;
        x = 10.0f;
        y = 5.0f;  
        health = 5; 
        boundryX = 100 - width;
        boundryY = 92 - height;

        printf("Player Constructed\n");
   }
   
void Player::setup(GLuint *newTextures) {
    x = 50.0f;
    y = 5.0f; 
    PlayerText = newTextures[0];
    PlayerLeftText = newTextures[1];
    PlayerRightText = newTextures[2];
    texture = newTextures[0];
    
    for(int i = 0; i < NUMBULLETS; ++i) 
        bullets[i].setup(newTextures[3]);
    
    printf("Player bullets constructed\n");
}

void Player::destroy() {
    //free(PlayerText);
   // free(PlayerLeftText);
   // free(PlayerRightText);
   // free(texture);
}

void Player::leftImage() {
    texture = PlayerLeftText;
}

void Player::rightImage() {
    texture = PlayerRightText;
}

void Player::stationaryImage() {
    texture = PlayerText;
}

void Player::draw() {
    //glColor3f(0.0, 1.0, 0.0);
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    if(x > boundryX)
        x = boundryX;
    if(y > boundryY)
        y = boundryY;
    if(health < 0)
        health = 0;

    glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, texture);
    
    glBegin(GL_POLYGON);
        glTexCoord2f(0.03f, 1.0f); 
        glVertex3f(x, y + height, 0.0);
        glTexCoord2f(1.03f, 1.0f);
        glVertex3f(x + width, y + height, 0.0);
        glTexCoord2f(1.03f, 0.0f);
        glVertex3f(x + width, y, 0.0);
        glTexCoord2f(0.03f, 0.0f);
        glVertex3f(x, y, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
  
    for(int i = 0; i < NUMBULLETS; ++i) {
        if(bullets[i].getVisible())
            bullets[i].moveUp();
            bullets[i].draw();
    } 
}

void Player::fire() {
    bool found = false;
    for(int i = 0; i < NUMBULLETS; ++i) {
        if(bullets[i].getVisible() == false) {
            bullets[i].fire(x + width/2, y + height, 1.75);
            found = true;
        }
        if(found)
            break;
    }
}  
     
int Player::getHealth() { return health; }
float Player::getX() { return x; }
float Player::getY() { return y; }
int Player::getWidth() { return width; }
int Player::getHeight() { return height; }
void Player::setBulletVisible(bool visible, int i) { bullets[i].setVisible(visible); }
bool Player::getBulletVisible(int i) { return bullets[i].getVisible(); }
float Player::getBulletX(int i) { return bullets[i].getX(); }
float Player::getBulletY(int i) { return bullets[i].getY(); }
int Player::getBulletWidth(int i) { return bullets[i].getWidth(); }
int Player::getBulletHeight(int i) { return bullets[i].getHeight(); }
void Player::reset() { x = 10; y = 5; health--;}
void Player::moveLeft() { x -= 0.5f; }
void Player::moveRight() { x += 0.5f; }
void Player::moveUp() { y += 0.25f; }
void Player::moveDown() { y -= 0.25f; }
