#include "Ship.h"

#include <stdlib.h>

Ship::Ship() {
        width = 5;
        height = 10;
        x = 10.0f;
        y = 5.0f;  
        health = 5; 
        boundryX = 100 - width;
        boundryY = 100 - height;

        printf("Ship Constructed\n");
   }
   
void Ship::setup(GLuint shipText, GLuint bulletText) {
    texture = shipText;
    bullets.setup(bulletText);
}

void Ship::draw() {
    //glColor3f(0.0, 1.0, 0.0);
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    if(x > boundryX)
        x = boundryX;
    if(y > boundryY)
        y = boundryY;

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

  
    //for(int i = 0; i < 5; ++i) {
        if(bullets.getVisible())
            bullets.draw();
    //}
  glDisable(GL_TEXTURE_2D);
}

void Ship::fire() {
  //  bool found = false;
  //  for(int i = 0; i < 5; ++i) {
        if(bullets.getVisible() == false) {
            bullets.fire(x + width/2, y + height, 1);
      //      printf("%d Bullet fire\n", i);
       //     found = true;
       // }
        //if(found)
         //   break;
    }

}  
     
int Ship::getHealth() { return health; }
float Ship::getX() { return x; }
float Ship::getY() { return y; }
void Ship::reset() { x = 0; y = 0; }
void Ship::moveLeft() { x -= 0.5f; }
void Ship::moveRight() { x += 0.5f; }
void Ship::moveUp() { y += 0.25f; }
void Ship::moveDown() { y -= 0.25f; }
