#include "Bullet.h"

#include <stdlib.h>

Bullet::Bullet() {
        width = 0.5;
        height = 3;
        x = 0.0f;
        y = 0.0f; 
         
        boundryX = 100 - width;
        boundryY = 95 - height;
        visible = true;
   }
   
void Bullet::setup(GLuint newText, float Width, float Height) {
    width = Width;
    height = Height;
    visible = true;
    x = -1;
    y = -1;
    texture = newText;
}

void Bullet::Tick() {    
    y += speed;
}

void Bullet::Tick(float X, float Y) {
  //  float angle;
   
    if(pow(pow(x-startX,2)+pow(y-startY,2), 0.5) >= distance)
    {
        x -= speed * directionX;
        y -= speed * directionY;
    } else {
        x -= speed * directionX;
        y -= speed * directionY; 
    }
    
   // angle = tan(opposite/adjacent);
   //     angle *= M_PI /180;
   // angle = 90.0f - angle;
   // x+= 1;
   // y += (opposite/adjacent)*0.1 * x;
   // x += speed * cos(angle);
   // y += speed * sin(angle);
    
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
    
    
    glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_POLYGON);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(x, y + height, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x + width, y + height, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x + width, y, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y, 0.0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}  

void Bullet::fire(float newX, float newY, float mSpeed) {
    x = newX;
    y = newY;
    speed = mSpeed;
    visible = true;
}

void Bullet::fire(float newX, float newY, float mSpeed, float X, float Y) {
    x = newX;
    y = newY;
    speed = mSpeed;
    visible = true;
    
    startX = x;
    startY = y;
    endX = X;
    endY = Y;
    float opposite = endX - startX;
    float adjacent = endY - startY;
    
    distance = pow(pow(opposite,2.0f) + pow(adjacent,2.0f), 0.5f);
    directionX = (opposite) / (distance+10);
    directionY = (adjacent) / (distance+10);
}

float Bullet::getX() { return x; }
float Bullet::getY() { return y; }
int Bullet::getWidth() { return width; }
int Bullet::getHeight() { return height; }
void Bullet::setVisible(bool Visible) { visible = Visible; if(!visible) {x = -1; y = -1;} }
bool Bullet::getVisible() { return visible; }
