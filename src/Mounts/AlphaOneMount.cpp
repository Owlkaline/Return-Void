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

void AlphaOneMount::individualClean() {
  cycle.clear();  
  cycle.erase(cycle.begin(), cycle.end());
  Nx.clear();  
  Nx.erase(Nx.begin(), Nx.end());
  Ny.clear();  
  Ny.erase(Ny.begin(), Ny.end());
}

void AlphaOneMount::defaults() {
  width = 25;
  height = 128;
  health = 35;//45;
}

void AlphaOneMount::erase() {
  for(unsigned int i = 0; i < cycle.size(); ++i) {
    if(cycle[i] > 400) {
      cycle.erase(cycle.begin() + i);
      Nx.erase(Nx.begin() + i);
      Ny.erase(Ny.begin() + i);
    }
  }
  for(unsigned int i = 0; i < bullets.size(); ++i) {
    if(!bullets[i]->getVisible())
      bullets.erase(bullets.begin() + i);
  }
}

void AlphaOneMount::tick(float x, float y, float deltaTime, float directionX, float directionY, float angle, bool isShooting) {
  for(unsigned int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update(deltaTime);
      if(bullets[i]->getIsBoss() && bullets[i]->hasExploded()) {
        printf("Boss bullet exploded\n");
        Nx.push_back(bullets[i]->getX());
        Ny.push_back(bullets[i]->getY());
        cycle.push_back(0);
        bullets[i]->setVisible(false);
      }
  }
  erase();
  int size = bullets.size();
  for(unsigned int i = 0; i < cycle.size(); ++i) {
    if((int)cycle[i] % 50 == 0) {
      angle = 0 + round(cycle[i]);
      for(unsigned int j = 0; j < 8; ++j) {
        printf("%d. new bullet\n", size+j);
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
    if((int)deltaTime % 1 == 0)
      cycle[i]+=1;
  }
}

