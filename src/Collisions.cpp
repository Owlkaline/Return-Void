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
          // Bullet x, y, width, height 
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
    
    // Collision between player bullets and enemyship
  }
 
 // std::vector<Mount*> Emounts = enemy.getMount();

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
