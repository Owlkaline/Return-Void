#include "../../include/Mounts/AlphaOneMount.h"

AlphaOneMount::AlphaOneMount() {
  visible = false;
  width = 25;
  height = 45;
}

AlphaOneMount::~AlphaOneMount() {
  clean();
}


void AlphaOneMount::setTexture() {
    if(tookDamage)
      glColor4f(1.0, 0.1, 0.1, 0.5f);
    glBindTexture(GL_TEXTURE_2D, getAlphaOneMountTexture());
}

void AlphaOneMount::reset() {

}

void AlphaOneMount::defaults() {
  width = 25;
  height = 128;
  health = 45;
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


  tick(isShooting);

  for(unsigned int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
    if(!bullets[i]->getVisible()) {
      if(bullets[i]->getIsBoss() && bullets[i]->getY() <= SPACE_Y_RESOLUTION/2+100) {
        Nx.push_back(bullets[i]->getX());
        Ny.push_back(bullets[i]->getY());
        cycle.push_back(0);
      }
      bullets.erase(bullets.begin() + i);
    }
  }

  int size = bullets.size();
  for(unsigned int i = 0; i < cycle.size(); ++i) {
    if(cycle[i] > 40) {
      cycle.erase(cycle.begin() + i);
      Nx.erase(Nx.begin() + i);
      Ny.erase(Ny.begin() + i);
    }
    if(cycle[i] % 5 == 0) {
      angle = 0 + 5*cycle[i]/5;
      for(unsigned int j = 0; j < 8; ++j) {
        bullets.push_back(new AlphaOnePlasma);
        bullets[size+j]->setup(0, 0, 0, 0, 0);
        float rad = (angle) * M_PI/180.0;
        float dirX = cos(-rad) * bullets[size+j]->getWidth();
        float dirY = sin(-rad) * bullets[size+j]->getHeight();
        float distance = pow(pow(dirY,2.0f) + pow(dirX,2.0f), 0.5f);
        dirX = dirX/distance;
        dirY = dirY/distance;

        bullets[size+j]->setIsBoss(false);
        bullets[size+j]->setup(Nx[i], Ny[i], dirX, dirY, angle);
        angle+=45;
      }
    }
    cycle[i]++;
  }
}

void AlphaOneMount::update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) {
  update(x, y, directionX, directionY, angle, true);
}

