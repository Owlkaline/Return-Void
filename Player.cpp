#include "Player.h"

#include <stdlib.h>

#define NUMBULLETS 10

Player::Player() {
    width = 5;
    height = 5;
    angle = 0;
    speed = 0.5f;
    boundryX = 100 - width;
    boundryY = 92 - height;
    globalTime = clock();
    printf("Player Constructed\n");
}
   
void Player::setup(GLuint *newTextures, float newAspectRatio) {
    x = 50.0f;
    y = 5.0f;
    angle = 0;
    aspectRatio = newAspectRatio;
   // width*=aspectRatio;
    height=5;//*aspectRatio;
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
        bullets[i].setup(newTextures[3], 0.5, 3);
    increment = 0;
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

void Player::Tick(float mouseX, float mouseY) {
    
    globalTime = clock();
    if(health < 0) {
        health = 0;
        alive = false;
        visible = false;    
    }
    float diffx = mouseX -x; 
    float diffy = mouseY -y;
    float distance = pow( (diffx * diffx) + (diffy * diffy) , 0.5);
    float directionX = (diffx) / (distance+10);
    float directionY = (diffy) / (distance+10);
    //angle = tan(directionY/directionX);


    if (diffx > 0.0 && diffy > 0.0) {
       angle = atan(diffy/diffx) *180 / M_PI ;
       angle = - angle -90;
    } else {
      angle =0;
    }



   // if(angle > 360) {
   //     angle = angle - 360;
   // } else if(angle < 0) {
   //     angle = 360 - angle;
   // }
        
    for(int i = 0; i < NUMBULLETS; ++i) {
        if(bullets[i].getVisible())    
            bullets[i].Tick();
    }
    increment++;
    if(increment > 100)
        increment = 0;
}

void Player::drawShip() {
    glPushMatrix();
    //glLoadIdentity();
    glTranslatef(x+width/2, y+width/2, 0); // M1 - 2nd translation
    glScalef(1,aspectRatio,1);        
    glRotatef(angle, 0.0f, 0.0f, 1.0f);                  // M2
    glTranslatef( -x, -y, 0);  // M3 - 1st translation  
   
    glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, texture);
    
    glBegin(GL_POLYGON);
      glTexCoord2f(0.0f, 1.0f); 
      glVertex3f(x-width/2, y+height/2, 0.0);
      glTexCoord2f(1.0f, 1.0f); 
      glVertex3f(x+width/2, y+height/2, 0.0);
      glTexCoord2f(1.0f, 0.0f); 
      glVertex3f(x+width/2, y-height/2, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x-width/2, y-height/2, 0.0);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
   // glRotatef(-45.0f, 0.0f, 0.0f, 1.0f);
                       // Reset The View
  //  glPushMatrix();
 //   glTranslatef(x,y, 0);
  //  glRotatef(45, 0.0, 0.0, 1.0f);
    //glTranslatef(x, y, 0);
  // glPopMatrix();
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
            bullets[i].fire(x + width/2, y + height-1, 1.75);
            found = true;
        }
        if(found)
            break;
    }
}  

void Player::moveLeft() { x -= speed; }
void Player::moveRight() { x += speed; }
void Player::moveUp() { y += speed; }
void Player::moveDown() { y -= speed; }

void Player::rotateRight() { angle--; }
void Player::rotateLeft() { angle++; }
void Player::setHealth(int newHealth) { health = newHealth; }
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

