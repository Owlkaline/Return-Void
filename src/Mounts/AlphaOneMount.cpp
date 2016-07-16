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
    if(cycle[i] % 20 == 0) {
      angle = 0 + cycle[i];
      for(unsigned int j = 0; j < 18; ++j) {
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
        angle+=20;
      }
    }
    cycle[i]++;

    /*angle = 0;
    for(unsigned int i = 0; i < 18; ++i) {     
        bullets.push_back(new AlphaOnePlasma);
        bullets[size+i]->setup(0, 0, 0, 0, 0);
        float rad = (angle) * M_PI/180.0;
        float dirX = cos(-rad) * bullets[size+i]->getWidth();
        float dirY = sin(-rad) * bullets[size+i]->getHeight();
        float distance = pow(pow(dirY,2.0f) + pow(dirX,2.0f), 0.5f);
        dirX = dirX/distance;
        dirY = dirY/distance;
      
        bullets[size+i]->setIsBoss(false);
        bullets[size+i]->setup(Nx[0], Ny[0], dirX, dirY, angle);
        angle += 20;
    }*/
  }
}

void AlphaOneMount::update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) {
  update(x, y, directionX, directionY, angle, true);
}

