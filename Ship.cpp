#include "Ship.h"

Ship::Ship() {
        width = 10;
        height = 10;
        x = 10.0f;
        y = 5.0f;  
        health = 5; 
        boundryX = 100 - width;
        boundryY = 100 - height; 
    }

void Ship::draw() {
    glColor3f(0.0, 1.0, 0.0);
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    if(x > boundryX)
        x = boundryX;
    if(y > boundryY)
        y = boundryY;
    //glPushMatrix();
    glBegin(GL_POLYGON);
        glVertex3f(x + 0.0, y + height, 0.0);
        glVertex3f(x + width, y + height, 0.0);
        glVertex3f(x + width, y + 0.0, 0.0);
        glVertex3f(x + 0.0, y + 0.0, 0.0);
    glEnd();
   // glPopMatrix();
}  
     
int Ship::getHealth() { return health; }
float Ship::getX() { return x; }
float Ship::getY() { return y; }
void Ship::reset() { x = 0; y = 0; }
void Ship::moveLeft() { x -= 0.5f; }
void Ship::moveRight() { x += 0.5f; }
void Ship::moveUp() { y += 0.25f; }
void Ship::moveDown() { y -= 0.25f; }
