#include "../../include/Ships/Ship.h"   
  
Ship::Ship() {

} 

void Ship::draw() {
  if(visible){
  glPushMatrix();
  glTranslatef(x, y, 0); // M1 - 2nd translation
  glRotatef(angle, 0.0f, 0.0f, 1.0f);  
  glTranslatef(-x, -y, 0); // M1 - 2nd translation
  glEnable(GL_TEXTURE_2D);
  
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  
 // glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x-width/2, y+height/2, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(x+width/2, y+height/2, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x+width/2, y-height/2, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x-width/2, y-height/2, 0.0);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();    
  }
  for(int i = 0; i < MAXWEAPONS; ++i) 
    WeaponMount[i]->draw(); 
}

void Ship::setup() {
  x = SPACE_X_RESOLUTION/2;
  y = 100;
  
  speed = 5;
  angle = 0;
  health = 60;
  width = 100;
  height = 100;
  visible = true;
  directionX = 1;
  directionY = 1; 
  
  textures[0] = txt::LoadTexture("Textures/Game/Ships/Ship.png");
  textures[1] = txt::LoadTexture("Textures/Game/Ships/ShipLeft.png");
  textures[2] = txt::LoadTexture("Textures/Game/Ships/ShipRight.png");
  
  const float mountPosX[MAXWEAPONS] = {18, -22, -2};
  const float mountPosY[MAXWEAPONS] = {0, 0, 50};
  
  for(int i = 0; i < MAXWEAPONS; ++i) {
    switch(i) {
      case 0:
      case 1:   
        WeaponMount[i] = new BasicMount;
        WeaponMount[i]->setup(BLUEPLASMA);
        break;
      case 2:
        WeaponMount[i] = new TriangleMount;
        WeaponMount[i]->setup();
        break;
    }
    
    WeaponMount[i]->setOffset(mountPosX[i], mountPosY[i]);
  }
}

void Ship::clean() {
    for(int i = 0; i < MAXWEAPONS; ++i) {
      WeaponMount[i]->clean();
     // delete WeaponMount[i];
    }
}
    
void Ship::takeDamage(int damage) {
  health -= damage;
  if(health <= 0)
    visible = false;
}
    
void Ship::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
    
  float diffx = mouseX - x;
  float diffy = mouseY - y;
  //diffy /= aspectRatio;
  distanceFromCursor = pow(pow(diffy,2.0f) + pow(diffx,2.0f), 0.5f);
  directionX = (diffx) / (distanceFromCursor);
  directionY = (diffy) / distanceFromCursor;//*aspectRatio) / (distance);
 
  if (diffx > 0.0 && diffy > 0.0) {//Quadrant 1
    angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
    angle = angle - 90.0f;
  }else if(diffx < 0 && diffy > 0) {//Quadrant 2
    angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
    angle = angle + 90.0f;
  } else     if(diffx < 0 && diffy < 0) {//Quadrant 3
     angle = (float)atan(diffy/diffx) *180.0f / (float)M_PI ;
     angle = angle+90.0f;
  } else     if(diffx > 0 && diffy < 0) {//Quadrant 4
     angle = (float)atan(diffy/diffx) * 180.0f / (float)M_PI ;
     angle = angle - 90.0f;
  }
   
 if(distanceFromCursor > MINIMUM_DISTANCETOSHIP) {
    if(keyState['W'] == BUTTON_DOWN || keyState['w'] == BUTTON_DOWN) {
      y+=speed*directionY;
      x+=speed*directionX;
    } 
  }
  if(keyState['S'] == BUTTON_DOWN || keyState['s'] == BUTTON_DOWN) {
    
    y-=speed*directionY;
    x-=speed*directionX;
  } 
    
  if(keyState['D'] == BUTTON_DOWN || keyState['d'] == BUTTON_DOWN) {
    x+=speed*directionY;
    y-=speed*directionX;
  } else if(keyState['A'] == BUTTON_DOWN || keyState['a'] == BUTTON_DOWN) {
    x-=speed*directionY;
    y+=speed*directionX;
  }  

  if(x < width/2) 
    x = width/2;
  if(x > SPACE_X_RESOLUTION-width/2)
    x = SPACE_X_RESOLUTION-width/2;
  if(y < height/2) 
    y = height/2;
  if(y > SPACE_Y_RESOLUTION-height/2)
    y = SPACE_Y_RESOLUTION-height/2;
    
    
  for(int i = 0; i < MAXWEAPONS; ++i) 
    WeaponMount[i]->update(x, y, directionX, directionY, angle);
}

bool Ship::getVisible() { return visible; }

int Ship::getNumOfMounts() { return MAXWEAPONS; }
int Ship::getNumOfBullets(int index) { return WeaponMount[index]->getNumBullets(); }
int Ship::bulletHit(int mIndex, int bIndex) { return WeaponMount[mIndex]->bulletHit(bIndex); }
  
float Ship::getX() { return x; }
float Ship::getY() { return y; }   
float Ship::getWidth() { return width; }
float Ship::getHeight() { return height; }   
float Ship::getDirectionX() { return directionX; }
float Ship::getDirectionY() { return directionY; }    
float Ship::getDistanceFromCursor() { return distanceFromCursor; }

float Ship::getBulletX(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletX(bIndex); }
float Ship::getBulletY(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletY(bIndex); }
float Ship::getBulletWidth(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletWidth(bIndex); }
float Ship::getBulletHeight(int mIndex, int bIndex) { return WeaponMount[mIndex]->getBulletHeight(bIndex); }




