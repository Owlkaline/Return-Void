#include "../../include/Mounts/TriangleMount.h"

TriangleMount::TriangleMount() {
  ticks=0;
}

TriangleMount::~TriangleMount() {
  clean();
}

void TriangleMount::draw() {
  for(unsigned int i = 0; i < bullets.size(); ++i)
    bullets[i]->draw();
      
  if(visible) {
    glPushMatrix();
    glTranslatef(x, y, 0); // M1 - 2nd translation
    glRotatef(angle, 0.0f, 0.0f, 1.0f);  
    glTranslatef(-x, -y, 0); // M1 - 2nd translation
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_TEXTURE_2D);  
    glBindTexture(GL_TEXTURE_2D, getTriangleMountTexture());
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
} 

void TriangleMount::reset() {

}

void TriangleMount::setup() { 
  x = -SPACE_X_RESOLUTION;
  y = -SPACE_Y_RESOLUTION;
  angle = 0;
  width = 32;
  height = 32;
  health = 20;
  timer = GREENPLASMATIMER;
  ticks = 0;
  visible = true;
  currentTexture = 0;
} 

void TriangleMount::setup(int variant) {
  setup();
}

void TriangleMount::update(float x, float y, float directionX, float directionY, float angle, bool isShooting) {  
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
    if(!bullets[i]->getVisible())
      bullets.erase(bullets.begin() + i);
  }
}

void TriangleMount::update(float x, float y, float directionX, float directionY, float angle, float Px, float Py) {
  update(x, y, directionX, directionY, angle, true);
}

void TriangleMount::addBullet() {
  bullets.push_back(new GreenPlasma);
}


