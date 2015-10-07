#include "Bullet.h"

#include <stdlib.h>

Bullet::Bullet() {
        width = 0.5;
        height = 3;
        x = 0.0f;
        y = 0.0f; 
         
        boundryX = 100 - width;
        boundryY = 95 - height;
        visible = false;
   }
   
void Bullet::setup(GLuint newText) {
    texture = newText;
}

    
void Bullet::draw() {
    if(!visible)
        return;
        
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    if(x > boundryX+height)
        x = boundryX;
    if(y > boundryY) {
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

float Bullet::getX() { return x; }
float Bullet::getY() { return y; }
int Bullet::getWidth() { return width; }
int Bullet::getHeight() { return height; }
void Bullet::setVisible(bool Visible) { visible = Visible; if(!visible) {x = 1; y = 1;} }
bool Bullet::getVisible() { return visible; }
void Bullet::moveUp() { y += speed; }
void Bullet::moveDown() { y -= speed; }
