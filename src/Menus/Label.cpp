#include "../../include/Menus/Label.h"

Label::Label() {

}

Label::~Label() {
  Texture = 0;
}

void Label::draw() {
  if(hasTexture) {  
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Texture);
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
  } else {
    if(isTimed) {
      if(ticks > 0)
        drawChar();
    } else {
      drawChar();
    }
  }
  if(hasBorder)
    drawBox();
}

void Label::clean() {

}

void Label::setup(float x, float y, float width, float height, char* filename) {
  Texture = txt::LoadTexture(filename);
  hasTexture = true;
  isTimed = false;
  hasBorder = false;
  length = 0;
  ticks = 0;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->scale = 0;
}

void Label::setup(float x, float y, float scale) {
  hasTexture = false;
  isTimed = false;
  hasBorder = false;
  length = 0;
  ticks = 0;
  this->x = x;
  this->y = y;
  this->scale = scale;
}

void Label::setup(float x, float y, float scale, bool timer) {
  hasTexture = false;
  hasBorder = false;
  isTimed = timer;
  length = 0;
  ticks = 0;
  this->x = x;
  this->y = y;
  this->scale = scale;
}

void Label::update() {
    if(isTimed) {
      ticks--;
      if(ticks <= 0)
        ticks = 0;
    } 
}

//Draws Text to the screen
void Label::drawChar() {
  glPushMatrix();
  glColor3f(R, G, B); // Text Colour
  //glRasterPos2i(x, y); //coordinates of text
  glTranslatef(x-length*10, y-10, 0);//*20, y, 0);

  // void * font = GLUT_BITMAP_TIMES_ROMAN_24;
  //GLUT_BITMAP_HELVETICA_18;//set font http://www.opengl.org/documentation/specs/glut/spec3/node76.html#SECTION000111000000000000000
  glScalef(scale,scale,scale);
  for(int i = 0; i < length; i++) {
    //glutBitmapCharacter(font, str[i]);//Draw character to screen
    glutStrokeCharacter(GLUT_STROKE_ROMAN , str[i]);
  }
   
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//return colours to the full amounts

  glPopMatrix();
}

void Label::setTexture(char* filename) {
  Texture = txt::LoadTexture(filename);
  hasTexture = true;
}

void Label::setText(const char* str, int length) {
  for(int i = 0; i < length; ++i)
    this->str[i] = str[i];
  this->length = length;
}

void Label::setTimer(int time) {
  ticks = time;
}

void Label::setColour(float R, float G, float B) {
  this->R = R;
  this->G = G;
  this->B = B;
}

void Label::drawBox() {
  float border = 5;
  glColor3f(0.0, 0.0, 0.0);
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

