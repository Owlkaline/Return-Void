#include "../../include/Mounts/AlphaOneMount.h"

AlphaOneMount::AlphaOneMount() {
  ticks=0;
}

AlphaOneMount::~AlphaOneMount() {
  clean();
}


void AlphaOneMount::setTexture() {
    glBindTexture(GL_TEXTURE_2D, getAlphaOneMountTexture());
} 

void AlphaOneMount::reset() {

}

void AlphaOneMount::defaults() { 
  width = 25;
  height = 128;
  health = 20;
} 

void AlphaOneMount::update(float x, float y, float directionX, float directionY, float angle, bool isShooting) {  
  float rad = angle* (float)M_PI / 180;
  float newX = (offsetX)*cos(rad) - (offsetY)*sin(rad);
  float newY = (offsetX)*sin(rad) + (offsetY)*cos(rad);
  this->x = x+newX;
  this->y = y+newY;
  this->angle = angle;
  dirX = directionX;
  dirY = directionY;
  
  if(isShooting)
    tick();
    
  for(unsigned int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
    if(!bullets[i]->getVisible())
      bullets.erase(bullets.begin() + i);
  }
}

void AlphaOneMount::update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) {
  update(x, y, directionX, directionY, angle, true);
}

