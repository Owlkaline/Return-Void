#include "../../include/Mounts/TriangleMount.h"

TriangleMount::TriangleMount() {
  visible = false;
  width = 32;
  height = 32;
}

TriangleMount::~TriangleMount() {
  clean();
}

std::string TriangleMount::getTexture() {
  //glBindTexture(GL_TEXTURE_2D, getHeroMountTexture(0));
  return "HeroMount1";
}

void TriangleMount::defaults() {
  width = 32;
  height = 32;
  health = 20;
}

void TriangleMount::draw(GraphicsHandler *graphics) {
   for(unsigned int i = 0; i < bullets.size(); ++i)
        bullets[i]->draw(graphics);

}
/*
void TriangleMount::update(float x, float y, float directionX, float directionY, float angle, bool isShooting) {
  float rad = angle* (float)M_PI / 180;
  float newX = (offsetX)*cos(rad) - (offsetY)*sin(rad);
  float newY = (offsetX)*sin(rad) + (offsetY)*cos(rad);

  this->x = x+newX;
  this->y = y+newY;
  this->angle = angle;

  dirX = directionX;
  dirY = directionY;

  if(isShooting) {
    tick(isShooting);
  } else {
    bulletTicks = GREENPLASMATIMER;
  }

  for(unsigned int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
    if(!bullets[i]->getVisible())
      bullets.erase(bullets.begin() + i);
  }
}

void TriangleMount::update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) {
  update(x, y, directionX, directionY, angle, true);
}
*/
