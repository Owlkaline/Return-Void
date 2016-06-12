#include "../../include/Namespaces/Collisions.h"

void Collisions::drawQuadTree() {
  // Quadrants
  // Top Left
  drawBox(SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4 * 3, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2);
    drawBox(SPACE_X_RESOLUTION/8, SPACE_Y_RESOLUTION/8 * 7, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8 * 3, SPACE_Y_RESOLUTION/8 * 7, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8 * 3, SPACE_Y_RESOLUTION/8 * 5, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8, SPACE_Y_RESOLUTION/8 * 5, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
  
  // Top Right
  drawBox(SPACE_X_RESOLUTION/4 * 3, SPACE_Y_RESOLUTION/4 * 3, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2);
    drawBox(SPACE_X_RESOLUTION/8 * 5, SPACE_Y_RESOLUTION/8 * 7, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8 * 7, SPACE_Y_RESOLUTION/8 * 7, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8 * 7, SPACE_Y_RESOLUTION/8 * 5, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8 * 5, SPACE_Y_RESOLUTION/8 * 5, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    
  // Bottom Right
  drawBox(SPACE_X_RESOLUTION/4 * 3, SPACE_Y_RESOLUTION/4, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2);
    drawBox(SPACE_X_RESOLUTION/8 * 5, SPACE_Y_RESOLUTION/8 * 3, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8 * 7, SPACE_Y_RESOLUTION/8 * 3, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8 * 7, SPACE_Y_RESOLUTION/8, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8 * 5, SPACE_Y_RESOLUTION/8, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
  
  // Bottom Left
  drawBox(SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2);
    drawBox(SPACE_X_RESOLUTION/8, SPACE_Y_RESOLUTION/8 * 3, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8 * 3, SPACE_Y_RESOLUTION/8 * 3, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8 * 3, SPACE_Y_RESOLUTION/8, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
    drawBox(SPACE_X_RESOLUTION/8, SPACE_Y_RESOLUTION/8, SPACE_X_RESOLUTION/4, SPACE_Y_RESOLUTION/4);
}

void Collisions::detect(Ship* ship, std::vector<Enemy*> enemy) {
  int shipQuad = getQuadrant(ship->getX(), ship->getY(), 1);
  
  int shipQuadTL = getQuadrant(ship->getX(), ship->getY()+ship->getHeight()/2, 1);
  int shipQuadTR = getQuadrant(ship->getX()+ship->getWidth()/2, ship->getY()+ship->getHeight()/2, 1);
  int shipQuadBR = getQuadrant(ship->getX()+ship->getWidth()/2, ship->getY(), 1);
  int shipQuadBL = getQuadrant(ship->getX(), ship->getY(), 1);
  
  // Ship x, y, width, height 
  float Sw = ship->getWidth();
  float Sh = ship->getHeight();
  float Sx = ship->getX();
  float Sy = ship->getY();
  
  // Enemy Number
  for(unsigned int i = 0; i < enemy.size(); ++i) {
  
    // Collision Of enemy bullets into player ship
    // The number weapon slot on the enemy
    for(int j = 0; j < enemy[i]->getNumOfMounts(); ++j) {
      // The bullets number for the weapon
      for(int k = 0; k < enemy[i]->getNumOfBullets(j); ++k) {
        int enemyQuad = getQuadrant(enemy[i]->getBulletX(j, k), enemy[i]->getBulletY(j, k), 1);
        if(enemyQuad == shipQuad || enemyQuad == shipQuadTR || enemyQuad == shipQuadTL || enemyQuad == shipQuadBR || enemyQuad == shipQuadBL) {
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
    
    if(enemy[i]->isVisible()) {
      // Enemy x, y, width, height 
      float Ew = enemy[i]->getWidth();
      float Eh = enemy[i]->getHeight();
      float Ex = enemy[i]->getX();
      float Ey = enemy[i]->getY();
    
      int enemyQuadTL = getQuadrant(enemy[i]->getX(), enemy[i]->getY()+enemy[i]->getHeight()/2, 1);
      int ememyQuadTR = getQuadrant(enemy[i]->getX()+enemy[i]->getWidth()/2, enemy[i]->getY()+enemy[i]->getHeight()/2, 1);
      int enemyQuadBR = getQuadrant(enemy[i]->getX()+enemy[i]->getWidth()/2, enemy[i]->getY(), 1);
      int enemyQuadBL = getQuadrant(enemy[i]->getX(), enemy[i]->getY(), 1);
      
      int enemyQuad = getQuadrant(enemy[i]->getX(), enemy[i]->getY(), 1);
    
      // Collision between player bullets and enemyship
      for(int j = 0; j < ship->getNumOfMounts(); ++j) {
        for(int k = 0; k < ship->getNumOfBullets(j); ++k) {
          int bulletQuad = getQuadrant(ship->getBulletX(j, k), ship->getBulletY(j, k),1);
          if(bulletQuad == enemyQuad || bulletQuad == ememyQuadTR || bulletQuad == enemyQuadTL || bulletQuad == enemyQuadBR || bulletQuad == enemyQuadBL) {
            // Ship bullet x, y, width, height 
            float Bw = ship->getBulletWidth(j, k);
            float Bh = ship->getBulletHeight(j, k);
            float Bx = ship->getBulletX(j, k);
            float By = ship->getBulletY(j, k);
            if( (Ex + Ew) >= Bx && Ex <= (Bx + Bw) && (Ey + Eh) >= By && Ey <= (By + Bh) ) {
              enemy[i]->takeDamage(ship->bulletHit(j, k));
            }
          } 
        }
      }
    }
  }
}

void Collisions::drawHitBoxes(Ship* ship, std::vector<Enemy*> enemy) {    
  // Enemy x, y, width, height 
  float Ew;
  float Eh;
  float Ex;
  float Ey;
  float Bw;
  float Bh;
  float Bx;
  float By;  
  for(unsigned int i = 0; i < enemy.size(); ++i) {  
    // Enemy x, y, width, height 
    Ew = enemy[i]->getWidth();
    Eh = enemy[i]->getHeight();
    Ex = enemy[i]->getX();
    Ey = enemy[i]->getY();
    drawBox(Ex, Ey, Ew, Eh);
       
    for(int j = 0; j < enemy[i]->getNumOfMounts(); ++j) {
      for(int k = 0; k < enemy[i]->getNumOfBullets(j); ++k) {
        Bw = enemy[i]->getBulletWidth(j, k);
        Bh = enemy[i]->getBulletHeight(j, k);
        Bx = enemy[i]->getBulletX(j, k);
        By = enemy[i]->getBulletY(j, k);
        drawBox(Bx, By, Bw, Bh);
      }
    }
  }

  float Sx = ship->getX();
  float Sy = ship->getY();
  float Sw = ship->getWidth();
  float Sh = ship->getHeight();
  drawBox(Sx, Sy, Sw, Sh);
  for(int i = 0; i < ship->getNumOfMounts(); ++i) {
    for(int j = 0; j < ship->getNumOfBullets(i); ++j) {
      Bw = ship->getBulletWidth(i, j);
      Bh = ship->getBulletHeight(i, j);
      Bx = ship->getBulletX(i, j);
      By = ship->getBulletY(i, j);
      drawBox(Bx, By, Bw, Bh);
    }
  }
}

void Collisions::drawBox(float x, float y, float width, float height) {
  float border = 2;
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_QUADS);
  
    // Left
    glVertex3f(x-width/2, y+height/2, 0.0);
    glVertex3f(x-width/2+border, y+height/2, 0.0);
    glVertex3f(x-width/2+border, y-height/2, 0.0);
    glVertex3f(x-width/2, y-height/2, 0.0);
    
    // Right
    glVertex3f(x+width/2, y+height/2, 0.0);
    glVertex3f(x+width/2-border, y+height/2, 0.0);
    glVertex3f(x+width/2-border, y-height/2, 0.0);
    glVertex3f(x+width/2, y-height/2, 0.0);
    
    // top
    glVertex3f(x+width/2, y+height/2, 0.0);
    glVertex3f(x+width/2, y+height/2-border, 0.0);
    glVertex3f(x-width/2, y+height/2-border, 0.0);
    glVertex3f(x-width/2, y+height/2, 0.0);
        
    // bottom
    glVertex3f(x+width/2, y-height/2, 0.0);
    glVertex3f(x+width/2, y-height/2+border, 0.0);
    glVertex3f(x-width/2, y-height/2+border, 0.0);
    glVertex3f(x-width/2, y-height/2, 0.0);
  
  glEnd();
  glColor3f(1.0, 1.0, 1.0);
}

int Collisions::getQuadrant(float x, float y, int level) {
  float halfX = SPACE_X_RESOLUTION/(2*level);
  float halfY = SPACE_Y_RESOLUTION/(2*level);
  
  if(level == MAXLEVEL) {
    if(x < halfX && y > halfY) {
      return 1*level;
    } else if (x < halfX && y < halfY) {
      return 2*level;
    } else if (x > halfX && y < halfY) {
      return 3*level;
    } else if (x < halfX && y < halfY) {
      return 4*level;
    }  
  } else { 
    return getQuadrant(x, y, level+1);
  }
  return 0;
}
