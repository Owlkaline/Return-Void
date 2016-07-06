#include "../../include/Mounts/HypnoMount.h"

HypnoMount::HypnoMount() {
  ticks=0;
}

HypnoMount::~HypnoMount() {
  clean();
}

void HypnoMount::draw() {
  for(unsigned int i = 0; i < bullets.size(); ++i)
    bullets[i]->draw();
      
  if(visible) {
    glPushMatrix();
    glTranslatef(x, y, 0); // M1 - 2nd translation
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  
    glTranslatef(-x, -y, 0); // M1 - 2nd translation
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);  
    glBindTexture(GL_TEXTURE_2D, getHypnoMountTexture(isLeft));
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x-width/2, y+height/2, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(x+width/2, y+height/2, 0.0);      
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(x+width/2, y-height/2, 0.0);      
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x-width/2, y-height/2, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix(); 
  }
}

void HypnoMount::reset() {

}

void HypnoMount::setup() { 
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_Y_RESOLUTION;
  angle = 0;
  width = 75/3.73;
  height = 75/3.73;
  health = 20;
  timer = 64;
  ticks = 0;
  visible = true;
} 

void HypnoMount::setup(int variant) {
  isLeft = variant;
  setup();
}

void HypnoMount::update(float x, float y, float directionX, float directionY, float angle, bool isShooting) {  

}

void HypnoMount::update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) {
 // dirX = directionX;
 // dirY = directionY;
 
  float diffx = Px - x;
  float diffy = Py - y;

  float distance = pow(pow(diffy,2.0f) + pow(diffx,2.0f), 0.5f);
  dirX = (diffx) / (distance);
  dirY = (diffy) / distance;
  
  float rad = angle* (float)M_PI / 180;
  float newX = (offsetX)*cos(rad) - (offsetY)*sin(rad);
  float newY = (offsetX)*sin(rad) + (offsetY)*cos(rad);
  this->x = x+newX;
  this->y = y+newY;
  this->angle = angle;
  
  tick();
    
  for(unsigned int i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
    if(!bullets[i]->getVisible())
      bullets.erase(bullets.begin() + i);
  }
}

void HypnoMount::addBullet() {
  bullets.push_back(new Spiral);
}


