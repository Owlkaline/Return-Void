#include "../../include/Mounts/BasicMount.h"

BasicMount::BasicMount() {
 // width = 8;
 // height = 64;
}

BasicMount::~BasicMount() {
  clean();
}


void BasicMount::setTexture() {
  if(currentTexture == 1) {
    glBindTexture(GL_TEXTURE_2D, getBasicMountBrightTexture());
  } else {
    glBindTexture(GL_TEXTURE_2D, getBasicMountTexture());
  }
}

void BasicMount::reset() {

}

void BasicMount::defaults() {
  width = 8;
  height = 64;
  health = 10;
}

void BasicMount::update(float x, float y, float directionX, float directionY, float angle, bool isShooting) {
  if(currentTexture == 1)
    currentTexture = 0;
  float rad = angle* (float)M_PI / 180;
  float newX = (offsetX)*cos(rad) - (offsetY)*sin(rad);
  float newY = (offsetX)*sin(rad) + (offsetY)*cos(rad);
  this->x = x+newX;
  this->y = y+newY;
  this->angle = angle;
  dirX = directionX;
  dirY = directionY;

  tick(isShooting);

  for(unsigned int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
    if(!bullets[i]->getVisible())
      bullets.erase(bullets.begin() + i);
  }
}

void BasicMount::update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) {
  update(x, y, directionX, directionY, angle, true);
}

