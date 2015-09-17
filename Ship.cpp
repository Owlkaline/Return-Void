#include "Ship.h"

Ship::Ship() {
        width = 2;
        height = 2;
        x = 10;
        y = 10;  
        health = 5; 
    }

void Ship::draw() {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(x + 0.0, y + 10.0, 0.0);
        glVertex3f(x + 10.0, y + 10.0, 0.0);
        glVertex3f(x + 10.0, y + 0.0, 0.0);
        glVertex3f(x + 0.0, y + 0.0, 0.0);
    glEnd();
}  
     
int Ship::getHealth() { return health; }
int Ship::getX() { return x; }
int Ship::getY() { return y; }
void Ship::reset() { x = 0; y = 0; }
void Ship::moveLeft() { x--; }
void Ship::moveRight() { x++; }
