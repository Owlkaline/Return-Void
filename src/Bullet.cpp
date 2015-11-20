#include "../include/Bullet.h"

#include <stdlib.h>

Bullet::Bullet() {
    width = 0.5;
    height = 6;
    x = 0.0f;
    y = 0.0f; 
         
    boundryX = 100 - width;
    boundryY = 95 - height;
    visible = true;
}
   
void Bullet::setup(GLuint newText, float width, float height, float aspectRatio) {
    this->aspectRatio = aspectRatio;
    this->width = width;
    this->height = height;
    visible = true;
    x = -1;
    y = -1;
    texture = newText;
    angle = 0;
}

void Bullet::Tick() {
        x += speed * directionX;
        y += speed * directionY;  
}
    
void Bullet::draw() {
    if(!visible)
        return;
        
    if(x < -width)
        visible = false;;
    if(y < -height)
        visible = false;
        
    if(x > boundryX+width)
        visible = false;
    if(y > boundryY+height) {
        visible = false;
    }
    
    glPushMatrix();
    //glLoadIdentity();
    glTranslatef(x, y, 0); // M1 - 2nd translation
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
}  

void Bullet::fire(float x, float y, float speed) {
    this->x = x;
    this->y = y;
    this->speed = speed;
    visible = true;
}

void Bullet::fire(float x, float y, float endX, float endY, float mSpeed) {
    this->x = x;
    this->y = y;
    speed = mSpeed;
    visible = true;
    
    startX = x;
    startY = y;
    this->endX = endX;
    this->endY = endY;
    float opposite = endX - startX;
    float adjacent = endY - startY;
    
    distance = pow(pow(opposite,2.0f) + pow(adjacent,2.0f), 0.5f);
    directionX = (opposite) / (distance+10);
    directionY = (adjacent) / (distance+10);   
}

void Bullet::fire(float x, float y, float directionX, float directionY,  float speed, float angle) {
    this->x = x;
    this->y = y;
    this->speed = speed;
    visible = true;
    
    this->directionX = directionX;
    this->directionY = directionY;
    this->angle = angle;   
}

float Bullet::getX() { return x; }
float Bullet::getY() { return y; }
int Bullet::getWidth() { return width; }
int Bullet::getHeight() { return height; }
void Bullet::setVisible(bool visible) { this->visible = visible; if(!this->visible) {x = -1; y = -1;} }
bool Bullet::getVisible() { return visible; }

