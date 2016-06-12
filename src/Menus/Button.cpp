#include "../../include/Menus/Button.h"

//GLuint Button::Texture = txt::LoadTexture("Textures/Menu/Button.png");


Button::Button() {

}

void Button::setup(float x, float y, float width, float height) {
  isSelected = false;
  hasBeenClicked = false;
  hasTexture = false;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  //Texture = txt::LoadTexture("Textures/Menu/Button.png");
}

/*GLuint Button::getTexture() {
  return Texture;
}

void Button::bindTexture() {
  glBindTexture(GL_TEXTURE_2D, Texture);
}*/

//Draws Text to the screen
void Button::drawChar() {
  glPushMatrix();
  glColor3f(R, G, B); // Text Colour
  //glRasterPos2i(x, y); //coordinates of text
  glTranslatef(x, y, 0);
  glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //colour blue

 // void * font = GLUT_BITMAP_TIMES_ROMAN_24;
  //GLUT_BITMAP_HELVETICA_18;//set font http://www.opengl.org/documentation/specs/glut/spec3/node76.html#SECTION000111000000000000000
   glScalef(1,1,1);
  for(int i = 0; i < length; i++) {
    //glutBitmapCharacter(font, str[i]);//Draw character to screen
    glutStrokeCharacter(GLUT_STROKE_ROMAN , str[i]);
  }
     
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//return colours to the full amounts

  glPopMatrix();
}

void Button::draw() {
  if(hasTexture) {
    if(hasBeenClicked) {
      glColor3f(0.0f, 0.0f, 0.0f);
    } else {
      glColor3f(1.0, 1.0, 1.0);
    }
  
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(x-width, y+height, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(x+width, y+height, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(x+width, y-height, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(x-width, y-height, 0.0);
    glEnd();  
  
    glDisable(GL_TEXTURE_2D);
  }
  drawChar();
}

void Button::update(float mouseX, float mouseY, unsigned int* mouseBtnState) {
  hasBeenClicked = false;
  if(mouseBtnState[GLUT_LEFT_BUTTON] == BUTTON_DOWN) {
    if(mouseX > x-width && mouseX < x+width) {
      if(mouseY > y-height && mouseY < y+height) {
        hasBeenClicked = true;
      }
    }
  } 
}

void Button::clean() {

}

bool Button::checkIfClicked() {
  return hasBeenClicked;
}

void Button::setTexture(char* filename) {
  Texture = txt::LoadTexture(filename);
  hasTexture = true;
}

void Button::setAlignment(int alignment) {
  align = alignment;
}

void Button::setText(char str[25], int length) {
  for(int i = 0; i < length; ++i)
    this->str[i] = str[i];
  this->length = length;
}

void Button::setColour(float R, float G, float B) {
  this->R = R;
  this->G = G;
  this->B = B;
}


