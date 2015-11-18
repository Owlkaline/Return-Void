#include "Bullet.h"

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
   
void Bullet::setup(GLuint newText, float Width, float Height, float aspectRatio) {
    this->aspectRatio = aspectRatio;
    width = Width;
    height = Height;
    visible = true;
    x = -1;
    y = -1;
    texture = newText;
}

void Bullet::Tick(float X, float Y) {    
    y += speed;
}

void Bullet::Tick() {
  
  if(pos)
    {
        x += speed * directionX;
        y += speed * directionY;
    } else {
        x -= speed * directionX;
        y -= speed * directionY; 
    }
    
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
    /*
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

    glDisable(GL_TEXTURE_2D);*/
}  

void Bullet::fire(float newX, float newY, float mSpeed) {
    x = newX;
    y = newY;
    speed = mSpeed;
    visible = true;
}

void Bullet::fire(float newX, float newY, float mSpeed, float X, float Y, bool pos) {
    this->pos = pos;
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
    
    if (opposite > 0.0 && adjacent > 0.0) {//Quadrant 1
        angle = atan(adjacent/opposite) *180 / M_PI ;
        angle = angle - 90;
    }else if(opposite < 0 && adjacent > 0) {//Quadrant 2
        angle = atan(adjacent/opposite) *180 / M_PI ;
        angle = angle + 90;
    } else     if(opposite < 0 && adjacent < 0) {//Quadrant 3
        angle = atan(adjacent/opposite) *180 / M_PI ;
        angle = angle+90;
    } else     if(opposite > 0 && adjacent < 0) {//Quadrant 4
        angle = atan(adjacent/opposite) * 180 / M_PI ;
        angle = angle - 90;
    }
}

float Bullet::getX() { return x; }
float Bullet::getY() { return y; }
int Bullet::getWidth() { return width; }
int Bullet::getHeight() { return height; }
void Bullet::setVisible(bool Visible) { visible = Visible; if(!visible) {x = -1; y = -1;} }
bool Bullet::getVisible() { return visible; }
