#include "Player.h"

#include <stdlib.h>

#define NUMBULLETS 10

Player::Player() {
    width = 5;
    height = 10;
    boundryX = 100 - width;
    boundryY = 92 - height;
    globalTime = clock();
    printf("Player Constructed\n");
}
   
void Player::setup(GLuint *newTextures) {
    x = 50.0f;
    y = 5.0f;
    health = 5;
    drawInvincible = true;
    fireRate = 2000;
    invincible = false;
    alive = true;
    visible = true; 
    PlayerText = newTextures[0];
    PlayerLeftText = newTextures[1];
    PlayerRightText = newTextures[2];
    texture = newTextures[0];
   // globalTime = clock();
    for(int i = 0; i < NUMBULLETS; ++i) 
        bullets[i].setup(newTextures[3], 0.25, 1.5);
    
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

void Player::Tick() {
    globalTime = clock();
    if(health < 0) {
        health = 0;
        alive = false;
        visible = false;    
    }
        
    for(int i = 0; i < NUMBULLETS; ++i) {
        if(bullets[i].getVisible())    
            bullets[i].Tick();
    }
}

void Player::drawShip() {
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
}

void Player::draw() {
    if(!visible)
        return;
        
    for(int i = 0; i < NUMBULLETS; ++i) {
        if(bullets[i].getVisible())           
            bullets[i].draw();
    } 
        
    //glColor3f(0.0, 1.0, 0.0);
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    if(x > boundryX)
        x = boundryX;
    if(y > boundryY)
        y = boundryY;
    
    if(!invincible) {
       drawShip();
    } else {
       if((globalTime - invincibleTime) > 20000) {
           invincible = false;
       } else {
           if(drawInvincible) {
               drawShip();
               if((globalTime - drawTime) > 1500) {
                   drawInvincible = false;
                   drawTime = globalTime;
               }
           } else {
               if((globalTime - drawTime) > 1500) {
                   drawInvincible = true;
                   drawTime = globalTime;
               }
           }
       }
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

void Player::setHealth(int newHealth) { health = newHealth; };
void Player::setVisible(bool Visible) { visible = Visible; }   
int Player::getWidth() { return width; }
int Player::getHealth() { return health; }
int Player::getHeight() { return height; }
float Player::getX() { return x; }
float Player::getY() { return y; }
bool Player::isAlive() { return alive; }
bool Player::getVisible() { return visible; }
bool Player::getInvincible() { return invincible; }

void Player::takeHealth(int Health) { health -= Health; if(health < 0) health = 0; }
void Player::setBulletVisible(bool Visible, int i) { bullets[i].setVisible(Visible); }
bool Player::getBulletVisible(int i) { return bullets[i].getVisible(); }
float Player::getBulletX(int i) { return bullets[i].getX(); }
float Player::getBulletY(int i) { return bullets[i].getY(); }
int Player::getBulletWidth(int i) { return bullets[i].getWidth(); }
int Player::getBulletHeight(int i) { return bullets[i].getHeight(); }

void Player::respawn(int X, int Y) { invincible = true; invincibleTime = globalTime; drawTime = globalTime; x = X; y = Y; visible = true;}
void Player::moveLeft() { x -= 0.5f; }
void Player::moveRight() { x += 0.5f; }
void Player::moveUp() { y += 0.45f; }
void Player::moveDown() { y -= 0.45f; }
