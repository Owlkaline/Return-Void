#include "../include/Collisions.h"

void Collisions::detect(Ship* ship, std::vector<Enemy*> enemy) {
  int shipQuad = getQuadrant(ship->getX(), ship->getY());
  
  // Ship x, y, width, height 
  float Sw = ship->getWidth();
  float Sx = ship->getX()-Sw/2;
  float Sy = ship->getY();
  float Sh = ship->getHeight();
  
  // Enemy Number
  for(int i = 0; i < enemy.size(); ++i) {
  
    // Collision Of enemy bullets into player ship
    // The number weapon slot on the enemy
    for(int j = 0; j < enemy[i]->getNumOfMounts(); ++j) {
      // The bullets number for the weapon
      for(int k = 0; k < enemy[i]->getNumOfBullets(j); ++k) {
        if(getQuadrant(enemy[i]->getBulletX(j, k), enemy[i]->getBulletY(j, k)) == shipQuad) {
          // Enemy bullet x, y, width, height 
          float Bx = enemy[i]->getBulletX(j, k);
          float By = enemy[i]->getBulletY(j ,k);
          float Bw = enemy[i]->getBulletWidth(j, k);
          float Bh = enemy[i]->getBulletHeight(j, k);
          if( (Sx + Sw) >= Bx && Sx <= (Bx + Bw) && (Sy + Sh) >= By && Sy <= (By + Bh) ) {
            ship->takeDamage(enemy[i]->bulletHit(j, k));
          }
        }
      }   
    }
    
    // Enemy x, y, width, height 
    float Ew = enemy[i]->getWidth();
    float Ex = enemy[i]->getX()-Ew/2;
    float Ey = enemy[i]->getY();
    float Eh = enemy[i]->getHeight();
      
    int enemyQuad = getQuadrant(enemy[i]->getX(), enemy[i]->getY());
    
    // Collision between player bullets and enemyship
    for(int j = 0; j < ship->getNumOfMounts(); ++j) {

      for(int k = 0; k < ship->getNumOfBullets(j); ++k) {
        if(getQuadrant(ship->getBulletX(j, k), ship->getBulletY(j, k)) == enemyQuad) {
          // Ship bullet x, y, width, height 
          float Bx = ship->getBulletX(j, k);
          float By = ship->getBulletY(j, k);
          float Bw = ship->getBulletWidth(j, k);
          float Bh = ship->getBulletHeight(j, k);
          if( (Ex + Ew) >= Bx && Ex <= (Bx + Bw) && (Ey + Eh) >= By && Ey <= (By + Bh) ) {
            enemy[i]->takeDamage(ship->bulletHit(j, k));
          }
        } 
      }
    }
  }
}

int Collisions::getQuadrant(float x, float y) {
  float halfX = SPACE_X_RESOLUTION/2;
  float halfY = SPACE_Y_RESOLUTION/2;
  if(x < halfX && y > halfY) {
    return 1;
  } else if (x < halfX && y < halfY) {
    return 2;
  } else if (x > halfX && y < halfY) {
    return 3;
  } else if (x < halfX && y < halfY) {
    return 4;
  }  
}
