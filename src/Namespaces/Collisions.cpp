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

void Collisions::detect(FighterShip* ship, std::vector<Enemy*> enemy, std::vector<Drops*> powerups) { 
  bool shipQuad[4];

  std::vector<unsigned int> shipMountQuad[4];
  std::vector<unsigned int> shipBulletQuad[4];

  std::vector<unsigned int> powerupQuad[4];

  std::vector<unsigned int> enemyQuad[4];
  std::vector<unsigned int> enemyNumQuad[4];
  std::vector<unsigned int> mountEnemyQuad[4];
  std::vector<unsigned int> bulletEnemyQuad[4];

  // Ship x, y, width, height
  float Sw = ship->getWidth()/2;
  float Sh = ship->getHeight()/2;
  float Sx = ship->getX();
  float Sy = ship->getY();

  shipQuad[getQuadrant(Sx-Sw, Sy-Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0)] = true;
  shipQuad[getQuadrant(Sx+Sw, Sy+Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0)] = true;
  shipQuad[getQuadrant(Sx-Sw, Sy+Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0)] = true;
  shipQuad[getQuadrant(Sx+Sw, Sy-Sh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0)] = true;

  // Powerups Quadrants
  for(unsigned int i = 0; i < powerups.size(); ++i) {
    float Pw = powerups[i]->getWidth()/2;
    float Ph = powerups[i]->getHeight()/2;
    float Px = powerups[i]->getX();
    float Py = powerups[i]->getY();
    int j[4];
    j[0] = getQuadrant(Px-Pw, Py-Ph, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
    j[1] = getQuadrant(Px+Pw, Py+Ph, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
    j[2] = getQuadrant(Px-Pw, Py+Ph, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
    j[3] = getQuadrant(Px+Pw, Py-Ph, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);

    powerupQuad[j[0]].push_back(i);
    if(j[1] != j[0])
      powerupQuad[j[1]].push_back(i);
    if(j[2] != j[0] && j[2] != j[1])
      powerupQuad[j[2]].push_back(i);
    if(j[3] != j[2] && j[3] != j[1] && j[3] != j[0])
      powerupQuad[j[3]].push_back(i);
  }
  // Player bullet Quadrants
  for(int i = 0; i < ship->getNumOfMounts(); ++i) {
    for(int j = 0; j < ship->getNumOfBullets(i); ++j) {
      float Bw = ship->getBulletWidth(i, j)/2;
      float Bh = ship->getBulletHeight(i, j)/2;
      float Bx = ship->getBulletX(i, j);
      float By = ship->getBulletY(i, j);
      int k[4];
      k[0] = getQuadrant(Bx-Bw, By-Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
      k[1] = getQuadrant(Bx+Bw, By+Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
      k[2] = getQuadrant(Bx-Bw, By+Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
      k[3] = getQuadrant(Bx+Bw, By-Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);

      shipMountQuad[k[0]].push_back(i);
      shipBulletQuad[k[0]].push_back(j);

      if(k[1] != k[0]) {
        shipMountQuad[k[1]].push_back(i);
        shipBulletQuad[k[1]].push_back(j);
      }
      if(k[2] != k[0] && k[2] != k[1]) {
        shipMountQuad[k[2]].push_back(i);
        shipBulletQuad[k[2]].push_back(j);
      }
      if(k[3] != k[2] && k[3] != k[1] && k[3] != k[0]) {
        shipMountQuad[k[3]].push_back(i);
        shipBulletQuad[k[3]].push_back(j);
      }
    }
  }
  // Enemy Quadrants
  for(unsigned int i = 0; i < enemy.size(); ++i) {
    float Ew = enemy[i]->getWidth()/2;
    float Eh = enemy[i]->getHeight()/2;
    float Ex = enemy[i]->getX();
    float Ey = enemy[i]->getY();
    if(Ey < SPACE_Y_RESOLUTION+Eh*2 && enemy[i]->isVisible()) {
      int j[4];
      j[0] = getQuadrant(Ex-Ew, Ey-Eh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
      j[1] = getQuadrant(Ex+Ew, Ey+Eh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
      j[2] = getQuadrant(Ex-Ew, Ey+Eh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
      j[3] = getQuadrant(Ex+Ew, Ey-Eh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);

      enemyQuad[j[0]].push_back(i);
      if(j[1] != j[0])
        enemyQuad[j[1]].push_back(i);
      if(j[2] != j[0] && j[2] != j[1])
        enemyQuad[j[2]].push_back(i);
      if(j[3] != j[2] && j[3] != j[1] && j[3] != j[0])
        enemyQuad[j[3]].push_back(i);
    }

    // Enemy Bullet quadrants
    for(int j = 0; j < enemy[i]->getNumOfMounts(); ++j) {
      for(int k = 0; k < enemy[i]->getNumOfBullets(j); ++k) {
        float Bw = enemy[i]->getBulletWidth(j, k)/2;
        float Bh = enemy[i]->getBulletHeight(j, k)/2;
        float Bx = enemy[i]->getBulletX(j, k);
        float By = enemy[i]->getBulletY(j, k);
        int l[4];
        l[0] = getQuadrant(Bx-Bw, By-Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
        l[1] = getQuadrant(Bx+Bw, By+Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
        l[2] = getQuadrant(Bx-Bw, By+Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);
        l[3] = getQuadrant(Bx+Bw, By-Bh, SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 1, 0);

        enemyNumQuad[l[0]].push_back(i);
        mountEnemyQuad[l[0]].push_back(j);
        bulletEnemyQuad[l[0]].push_back(k);

        if(l[1] != l[0]) {
          enemyNumQuad[l[1]].push_back(i);
          mountEnemyQuad[l[1]].push_back(j);
          bulletEnemyQuad[l[1]].push_back(k);
        }
        if(l[2] != l[0] && l[2] != l[1]) {
          enemyNumQuad[l[2]].push_back(i);
          mountEnemyQuad[l[2]].push_back(j);
          bulletEnemyQuad[l[2]].push_back(k);
        }
        if(l[3] != l[2] && l[3] != l[1] && l[3] != l[0]) {
          enemyNumQuad[l[3]].push_back(i);
          mountEnemyQuad[l[3]].push_back(j);
          bulletEnemyQuad[l[3]].push_back(k);
        }
      }
    }
  }

  // Check collision within same quadrants
  for(int i = 0; i < 4; ++i) {
    for(unsigned int j = 0; j < enemyQuad[i].size(); ++j) {
      int k = enemyQuad[i][j];
      float Ew = enemy[k]->getWidth()/2;
      float Eh = enemy[k]->getHeight()/2;
      float Ex = enemy[k]->getX();
      float Ey = enemy[k]->getY();

      // Collision between ship bullets and enemy
      for(unsigned int l = 0; l < shipMountQuad[i].size(); ++l) {
        int m = shipMountQuad[i][l];
        int n = shipBulletQuad[i][l];

        float Bw = ship->getBulletWidth(m, n)/2;
        float Bh = ship->getBulletHeight(m, n)/2;
        float Bx = ship->getBulletX(m, n);
        float By = ship->getBulletY(m, n);
        if( (Bx + Bw) >= (Ex-Ew) && (Bx-Bw) <= (Ex + Ew) && (By + Bh) >= (Ey-Eh) && (By-Bh) <= (Ey + Eh) ) {
          enemy[k]->takeDamage(ship->bulletHit(m, n));
        }
      }

      if(shipQuad[i] == true) {
      // Collision between Ship and Enemy
        if( (Ex + Ew) >= (Sx-Sw) && (Ex-Ew) <= (Sx + Sw) && (Ey + Eh) >= (Sy-Sh) && (Ey-Eh) <= (Sy + Sh) ) {
          enemy[k]->takeDamage(10000);
          ship->takeDamage(5);
        }
      }
    }

    if(shipQuad[i] == true) {
      // Collision between Ship and enemy bullets
      for(unsigned int j = 0; j < enemyNumQuad[i].size(); ++j) {
        int k = enemyNumQuad[i][j];
        int l = mountEnemyQuad[i][j];
        int m = bulletEnemyQuad[i][j];

        float Bw = enemy[k]->getBulletWidth(l, m)/2;
        float Bh = enemy[k]->getBulletHeight(l, m)/2;
        float Bx = enemy[k]->getBulletX(l, m);
        float By = enemy[k]->getBulletY(l, m);
        if( (Sx + Sw) >= (Bx-Bw) && (Sx-Sw) <= (Bx + Bw) && (Sy + Sh) >= (By-Bh) && (Sy-Sh) <= (By + Bh) ) {
          ship->takeDamage(enemy[k]->bulletHit(l, m));
        }
      }

      // Collision between Ship and powerups
      for(unsigned int j = 0; j < powerupQuad[i].size(); ++j) {
        int k = powerupQuad[i][j];
        if(!powerups[k]->getCollected()) {
          float Pw = powerups[k]->getWidth()/2;
          float Ph = powerups[k]->getHeight()/2;
          float Px = powerups[k]->getX();
          float Py = powerups[k]->getY();
          if( (Sx + Sw) >= (Px-Pw) && (Sx-Sw) <= (Px + Pw) && (Sy + Sh) >= (Py-Ph) && (Sy-Sh) <= (Py + Ph) ) {
            ship->collect(powerups[k]->getType());
          }
        }
      }
    }
  }
  
  for(int i = 0; i < 4; ++i) {
    enemyQuad[i].clear();
    powerupQuad[i].clear();
    enemyNumQuad[i].clear();
    shipMountQuad[i].clear();
    mountEnemyQuad[i].clear();
    shipBulletQuad[i].clear();
    bulletEnemyQuad[i].clear();
  }
}

void Collisions::drawHitBoxes(FighterShip* ship, std::vector<Enemy*> enemy, std::vector<Drops*> powerups) {    
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


  float Sw = ship->getWidth()/2;
  float Sh = ship->getHeight()/2;
  float Sx = ship->getX();
  float Sy = ship->getY();
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

  float Pw;
  float Ph;
  float Px;
  float Py;
  for(unsigned int i = 0; i < powerups.size(); ++i) {
    // Enemy x, y, width, height
    Pw = powerups[i]->getWidth()/2;
    Ph = powerups[i]->getHeight()/2;
    Px = powerups[i]->getX();
    Py = powerups[i]->getY();
    drawBox(Px, Py, Pw, Ph);
  }
}

void Collisions::drawBox(float x, float y, float width, float height) {
  float border = 2;
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_QUADS);

    // Left
    glVertex3f(x-width, y+height, 0.0);
    glVertex3f(x-width+border, y+height, 0.0);
    glVertex3f(x-width+border, y-height, 0.0);
    glVertex3f(x-width, y-height, 0.0);

    // Right
    glVertex3f(x+width, y+height, 0.0);
    glVertex3f(x+width-border, y+height, 0.0);
    glVertex3f(x+width-border, y-height, 0.0);
    glVertex3f(x+width, y-height, 0.0);

    // top
    glVertex3f(x+width, y+height, 0.0);
    glVertex3f(x+width, y+height-border, 0.0);
    glVertex3f(x-width, y+height-border, 0.0);
    glVertex3f(x-width, y+height, 0.0);

    // bottom
    glVertex3f(x+width, y-height, 0.0);
    glVertex3f(x+width, y-height+border, 0.0);
    glVertex3f(x-width, y-height+border, 0.0);
    glVertex3f(x-width, y-height, 0.0);

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
