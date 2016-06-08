#include "../include/BasicMount.h"

BasicMount::BasicMount() {

}

void BasicMount::setup(float offsetX, float offsetY) { 
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_Y_RESOLUTION;
  tick = 0;
  angle = 0;
  width = 8;
  height = 64;
  this->offsetX = offsetX;
  this->offsetY = offsetY;
  t = clock();
  Texture = txt::LoadTexture("Textures/Game/Weapons/BasicMount.png");
} 

void BasicMount::fire(float directionX, float directionY) {
  //t = clock();
  tick = 0;
  bullets.push_back(new BluePlasma);
  int i = bullets.size()-1;
  bullets[i]->setup(x, y, directionX, directionY, angle);
  bullets[i]->setVisible(true);
}

void BasicMount::update(float x, float y, float directionX, float directionY, float angle) {
  tick++;
  
  float rad = angle* (float)M_PI / 180;
  float newX = (offsetX)*cos(rad) - (offsetY)*sin(rad);
  float newY = (offsetX)*sin(rad) + (offsetY)*cos(rad);
  this->x = x+newX;
  this->y = y+newY;
  this->angle = angle;

  if(tick > 10)
    fire(directionX, directionY);
  
  for(unsigned int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
    if(!bullets[i]->getVisible())
      bullets.erase(bullets.begin() + i);
  }
}

void BasicMount::draw() {
  for(unsigned int i = 0; i < bullets.size(); ++i)
    bullets[i]->draw();
    
  glPushMatrix();
  glTranslatef(x, y, 0); // M1 - 2nd translation
  glRotatef(angle, 0.0f, 0.0f, 1.0f);  
  glTranslatef(-x, -y, 0); // M1 - 2nd translation
  glEnable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);  
  glBindTexture(GL_TEXTURE_2D, Texture);
  glBegin(GL_QUADS);
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

void BasicMount::reset() {

}

void BasicMount::clean() {

}
