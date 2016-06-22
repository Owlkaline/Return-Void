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

void Collisions::detect(Ship* ship, std::vector<Enemy*> enemy, std::vector<Drops*> powerups) {
 // int shipQuads[4];
 // Point* enemyBulletQuads[4];
 /* 
  float Sw = ship->getWidth()/2;
  float Sh = ship->getHeight()/2;
  float Sx = ship->getX();
  float Sy = ship->getY();
 
  int index = getQuadrant(Sx-Sw, Sy-Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
  shipQuads[index] = 1;
  index = getQuadrant(Sx+Sw, Sy+Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
  shipQuads[index] = 1;
  index = getQuadrant(Sx-Sw, Sy+Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
  shipQuads[index] = 1;
  index = getQuadrant(Sx+Sw, Sy-Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
  shipQuads[index] = 1;
  
  for(unsigned int i = 0; i < enemy.size(); ++i) {
    for(int j = 0; j < enemy[i]->getNumOfMounts(); ++j) {
      for(int k = 0; k < enemy[i]->getNumOfBullets(j); ++k) {
        float Bw = enemy[i]->getBulletWidth(j, k)/2;
        float Bh = enemy[i]->getBulletHeight(j, k)/2;
        float Bx = enemy[i]->getBulletX(j, k);
        float By = enemy[i]->getBulletY(j, k);
        i = getQuadrant(Bx-Bw, By-Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
        enemyBulletQuads[i] = new Point(Bx-Bw, By-Bh, i);
        i = getQuadrant(Bx+Sw, By+Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
        enemyBulletQuads[i] = new Point(Bx+Bw, By+Bh, i);
        i = getQuadrant(Bx-Bw, By+Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
        enemyBulletQuads[i] = new Point(Bx-Bw, By+Bh, i);
        i = getQuadrant(Bx+Bw, By-Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
        enemyBulletQuads[i] = new Point(Bx+Bw, By-Bh, i);
      }
    }
  }
  
  
  for(int i = 0; i < 4; ++i) {
    if(shipQuads[i] == 1) {
      for(unsigned int j = 0; j < enemy.size(); ++j) {
      //for(int l = 0; l < enemyQuads[i].getSize(); ++l) {
        int l = enemyBulletQuads[i][4].getPos();
        if(l != -1) {
          for(int m = 0; m < enemy[l]->getNumOfMounts(); ++m) {
            for(int k = 0; k < enemy[l]->getNumOfBullets(m); ++k) {
              float Bw = enemy[l]->getBulletWidth(l, k)/2;
              float Bh = enemy[l]->getBulletHeight(l, k)/2;
              float Bx = enemy[l]->getBulletX(l, k);
              float By = enemy[l]->getBulletY(l, k);
              if( (Sx + Sw) >= Bx && Sx <= (Bx + Bw) && (Sy + Sh) >= By && Sy <= (By + Bh) ) {
                ship->takeDamage(enemy[l]->bulletHit(m, k));
              }
            }
          }
        }
      }
    }
      //if( (Sx + Sw) >= Bx && Sx <= (Bx + Bw) && (Sy + Sh) >= By && Sy <= (By + Bh) )

  }*/
  
  //int x = shipQuads[0][0].getX();
     
  // Ship x, y, width, height 
  float Sw = ship->getWidth();
  float Sh = ship->getHeight();
 // float Sx = ship->getX()-Sw/2;
  float Sx = ship->getX()-Sw/2;
  float Sy = ship->getY();
  
  int shipQuad[4];
  int shipBulletQuad[4];
  int enemyQuad[4];
  int enemyBulletQuad[4];
  int powerupQuad[4];
  
  shipQuad[0] = getQuadrant(Sx-Sw, Sy-Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
  shipQuad[1] = getQuadrant(Sx+Sw, Sy+Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
  shipQuad[2] = getQuadrant(Sx-Sw, Sy+Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
  shipQuad[3] = getQuadrant(Sx+Sw, Sy-Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
  
  // Enemy
  for(unsigned int i = 0; i < enemy.size(); ++i) {
    // Enemy x, y, width, height 
    float Ew = enemy[i]->getWidth()/2;
    float Eh = enemy[i]->getHeight()/2;
    float Ex = enemy[i]->getX();
    float Ey = enemy[i]->getY();
    
    enemyQuad[0] = getQuadrant(Ex-Ew, Ey-Eh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
    enemyQuad[1] = getQuadrant(Ex+Ew, Ey+Eh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
    enemyQuad[2] = getQuadrant(Ex-Ew, Ey+Eh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
    enemyQuad[3] = getQuadrant(Ex+Ew, Ey-Eh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
    
    for(int j = 0; j < enemy[i]->getNumOfMounts(); ++j) {
      for(int k = 0; k < enemy[i]->getNumOfBullets(j); ++k) {
        float Bw = enemy[i]->getBulletWidth(j, k)/2;
        float Bh = enemy[i]->getBulletHeight(j, k)/2;
        float Bx = enemy[i]->getBulletX(j, k);
        float By = enemy[i]->getBulletY(j, k);
        enemyBulletQuad[0] = getQuadrant(Bx-Bw, By-Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
        enemyBulletQuad[1] = getQuadrant(Bx+Bw, By+Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
        enemyBulletQuad[2] = getQuadrant(Bx-Bw, By+Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
        enemyBulletQuad[3] = getQuadrant(Bx+Bw, By-Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
        bool isDone = false;
        for(int l = 0; l < 4; l++) {
          for(int m = 0; m < 4; ++l) {
            if(enemyBulletQuad[l] == shipQuad[m]) {
              if( (Sx + Sw) >= Bx && Sx <= (Bx + Bw) && (Sy + Sh) >= By && Sy <= (By + Bh) ) {
                ship->takeDamage(enemy[i]->bulletHit(j, k));
              }
              isDone = true;
            }
            if(isDone)
              break;
          }
          if(isDone)
            break;
        }         
      }
    }   
  
    
    if(enemy[i]->isVisible()) {

    
      // Collision between player bullets and enemyship
      for(int j = 0; j < ship->getNumOfMounts(); ++j) {
        for(int k = 0; k < ship->getNumOfBullets(j); ++k) {
          float Bw = ship->getBulletWidth(j, k)/2;
          float Bh = ship->getBulletHeight(j, k)/2;
          float Bx = ship->getBulletX(j, k);
          float By = ship->getBulletY(j, k);
          shipBulletQuad[0] = getQuadrant(Bx-Bw, By-Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
          shipBulletQuad[1] = getQuadrant(Bx+Bw, By+Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
          shipBulletQuad[2] = getQuadrant(Bx-Bw, By+Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
          shipBulletQuad[3] = getQuadrant(Bx+Bw, By-Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
          bool isDone = false;
          for(int l = 0; l < 4; l++) {
            for(int m = 0; m < 4; ++l) {
              if(shipBulletQuad[l] == enemyQuad[m]) {
                if( (Bx + Bw) >= Ex && Bx <= (Ex + Ew) && (By + Bh) >= Ey && By <= (Ey + Eh) ) {
                  enemy[i]->takeDamage(ship->bulletHit(j, k));
                }
                isDone = true;
              }
              if(isDone)
                break;
            }
            if(isDone)
              break;
          }   
        } 
      }      
      // Enemy into Player
      bool isDone = false;
      for(int l = 0; l < 4; l++) {
        for(int m = 0; m < 4; ++l) {
          if(enemyQuad[l] == shipQuad[m]) {
            if( (Ex + Ew) >= Sx && Ex <= (Sx + Sw) && (Ey + Eh) >= Sy && Ey <= (Sy + Sh) ) {
              enemy[i]->takeDamage(10000);
              ship->takeDamage(5);
            }
            isDone = true;
          }
          if(isDone)
            break;
        }
        if(isDone)
          break;
      } 
    }
  }
  
  // Powerup collision into player
  for(unsigned int i = 0; i < powerups.size(); ++i) {
    float Pw = powerups[i]->getWidth()/2;
    float Ph = powerups[i]->getHeight()/2;
    float Px = powerups[i]->getX();
    float Py = powerups[i]->getY();
    powerupQuad[0] = getQuadrant(Px-Pw, Py-Ph, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
    powerupQuad[1] = getQuadrant(Px+Pw, Py+Ph, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
    powerupQuad[2] = getQuadrant(Px-Pw, Py+Ph, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
    powerupQuad[3] = getQuadrant(Px+Pw, Py-Ph, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
    bool isDone = false;
    for(int l = 0; l < 4; l++) {
      for(int m = 0; m < 4; ++l) {
        if(powerupQuad[l] == shipQuad[m]) {
          if( (Sx + Sw) >= Px && Sx <= (Px + Pw) && (Sy + Sh) >= Py && Sy <= (Py + Ph) ) {
            ship->collect(powerups[i]->getType());
          }
          isDone = true;
        }
        if(isDone)
          break;
      }
      if(isDone)
        break;
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
    Ew = enemy[i]->getWidth()/2;
    Eh = enemy[i]->getHeight()/2;
    Ex = enemy[i]->getX();
    Ey = enemy[i]->getY();
    drawBox(Ex, Ey, Ew, Eh);
       
    for(int j = 0; j < enemy[i]->getNumOfMounts(); ++j) {
      for(int k = 0; k < enemy[i]->getNumOfBullets(j); ++k) {
        Bw = enemy[i]->getBulletWidth(j, k)/2;
        Bh = enemy[i]->getBulletHeight(j, k)/2;
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
      Bw = ship->getBulletWidth(i, j)/2;
      Bh = ship->getBulletHeight(i, j)/2;
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

int Collisions::getQuadrant(float x, float y, int xBoundry, int yBoundry, int level, int quadrant) {
  
  if(level != MAXLEVEL) {
    if(x < xBoundry && y > yBoundry) {
      return getQuadrant(x, y, xBoundry/2, yBoundry/2 * 3, level+1, quadrant+0);
      
    } else if (x < xBoundry && y < yBoundry) {
      return getQuadrant(x, y, xBoundry/2, yBoundry/2, level+1, quadrant+1);
      
    } else if (x > xBoundry && y > yBoundry) {
      return getQuadrant(x, y, xBoundry/2 * 3, yBoundry/2 * 3, level+1, quadrant+2);
      
    } else if (x > xBoundry && y < yBoundry) {
      return getQuadrant(x, y, xBoundry/2 * 3, yBoundry/2, level+1, quadrant+3);      
    }  
  } else {
    return quadrant;
  } 
  return 0;
}
