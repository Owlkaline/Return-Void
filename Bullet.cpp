#include "Bullet.h"

#include <stdlib.h>

Bullet::Bullet() {
        width = 3;
        height = 4;
        x = 0.0f;
        y = 0.0f;  
        boundryX = 100 - width;
        boundryY = 100 - height;
        isVisible = false;
        //setup();
        printf("Bullet Constructed\n");
   }
   
void Bullet::setup(GLuint newText) {
    texture = newText;
}

    
void Bullet::draw() {
    moveUp();   
    //glColor3f(0.0, 1.0, 0.0);
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    if(x > boundryX+height)
        x = boundryX;
    if(y > boundryY) {
      //  y = boundryY;
        isVisible = false;
    }
    
    
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

    glDisable(GL_TEXTURE_2D);
}  

void Bullet::fire(float newX, float newY, float mSpeed) {
    x = newX - width/2;
    y = newY;
    speed = mSpeed;
    isVisible = true;
    //printf("new bullet fired\n");
  //  draw();
}

float Bullet::getX() { return x; }
float Bullet::getY() { return y; }
bool Bullet::getVisible() { return isVisible; }
void Bullet::moveUp() { y += speed; }
void Bullet::moveDown() { y -= speed; }
