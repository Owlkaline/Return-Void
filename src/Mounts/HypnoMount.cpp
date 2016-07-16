#include "../../include/Mounts/HypnoMount.h"

HypnoMount::HypnoMount() {
  
}

HypnoMount::~HypnoMount() {
  clean();
}

void HypnoMount::setTexture() {
  glBindTexture(GL_TEXTURE_2D, getHypnoMountTexture(isLeft));
}

void HypnoMount::reset() {

}

void HypnoMount::defaults() { 
  width = 75/3.73;
  height = 75/3.73;
  health = 20;
} 

void HypnoMount::update(float x, float y, float directionX, float directionY, float angle, bool isShooting) {  

}

void HypnoMount::update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) {
 // dirX = directionX;
 // dirY = directionY;
 
  float diffx = Px - x;
  float diffy = Py - y;

  float distance = pow(pow(diffy,2.0f) + pow(diffx,2.0f), 0.5f);
  dirX = (diffx) / (distance);
  dirY = (diffy) / distance;
  
  float rad = angle* (float)M_PI / 180;
  float newX = (offsetX)*cos(rad) - (offsetY)*sin(rad);
  float newY = (offsetX)*sin(rad) + (offsetY)*cos(rad);
  this->x = x+newX;
  this->y = y+newY;
  this->angle = angle;
  
  tick();
    
  for(unsigned int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
    if(!bullets[i]->getVisible())
      bullets.erase(bullets.begin() + i);
  }
}


