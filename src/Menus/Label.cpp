#include "../../include/Menus/Label.h"

Label::Label() {

}

Label::~Label() {
  Texture = 0;
}

void Label::draw() {
  if(visible) {
    if(isFilled) {
      glColor3f(fillR, fillG, fillB);
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
      glColor3f(1.0f, 1.0f, 1.0f);
    }
    if(hasTexture) {  
     if(disabled)
        glColor4f(1.0, 1.0, 1.0, 0.5);
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
      glColor3f(1.0f, 1.0f, 1.0f);
      glDisable(GL_TEXTURE_2D);
    } else {
      if(isTimed) {
        if(ticks > 0)
          drawChar();
      } else {
        //text.draw();
        drawChar();
      }
    }
    if(hasBorder)
      drawBox();
  }
  glColor3f(1.0, 1.0f, 1.0);
}

void Label::clean() {

}

void Label::setupGLC(float scaleX, float scaleY) {
  settings.Load();
  float ratioX = settings.getCurrentWindowWidth()/(float)SPACE_X_RESOLUTION;
  float ratioY = settings.getCurrentWindowHeight()/(float)SPACE_Y_RESOLUTION;
  // Set up and initialize GLC
  ctx = glcGenContext();
  glcContext(ctx);
  glcAppendCatalog("/usr/lib/X11/fonts/Type1/");

  // Create a font "Palatino Bold"
  myFont = glcGenFontID();
  #ifdef __WIN32__
    glcNewFontFromFamily(myFont, "Palatino Linotype");
  #else
    glcNewFontFromFamily(myFont, "Palatino");
  #endif
  //glcFontFace(myFont, "Bold");
  glcFont(myFont);
      // Render the text at a size of 100 points
  glcScale(30*ratioX, 30*ratioY);
}

void Label::setup(float x, float y, float width, float height, char* filename) {
  Texture = txt::LoadTexture(filename);
  hasTexture = true;
  isTimed = false;
  hasBorder = false;
  isFilled = false;
  visible = true;
  disabled = false;
  length = 0;
  ticks = 0;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->scaleX = 1;
  this->scaleY = 1;
  R = 0;
  B = 0;
  G = 0;
  setupGLC(scaleX, scaleY);
}

void Label::setup(float x, float y, float scaleX, float scaleY) {
  hasTexture = false;
  isTimed = false;
  hasBorder = false;
  isFilled = false;
  visible = true;
  disabled = false;
  length = 0;
  ticks = 0;
  this->x = x;
  this->y = y;
  this->scaleX = scaleX;
  this->scaleY = scaleY;
  R = 0;
  B = 0;
  G = 0;
  setupGLC(scaleX, scaleY);
}

void Label::setup(float x, float y, float scaleX, float scaleY, bool timer) {
  hasTexture = false;
  hasBorder = false;
  isFilled = false;
  visible = true;
  disabled = false;
  isTimed = timer;
  length = 0;
  ticks = 0;
  this->x = x;
  this->y = y;
  this->scaleX = scaleX;
  this->scaleY = scaleY;
  R = 0;
  B = 0;
  G = 0;
  setupGLC(scaleX, scaleY);
}

void Label::update(float deltaTime) {
    if(isTimed) {
      ticks-=1*deltaTime;
      if(ticks <= 0)
        ticks = 0;
    } 
}

//Draws Text to the screen
void Label::drawChar() {
  // Render "Hello world!"
  glColor3f(R, G, B);
  glRasterPos2f(x-length*10, y);
  glcRenderString(str.c_str());
}

void Label::setTexture(char* filename) {
  Texture = txt::LoadTexture(filename);
  hasTexture = true;
}

void Label::setText(std::string str, int length) {
 // for(int i = 0; i < length; ++i)
   this->length = length;
   this->str = str;
  //text.setup(x, y, (char*)str);
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

