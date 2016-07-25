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
  this->scale = 0;
  R = 0;
  B = 0;
  G = 0;
}

void Label::setup(float x, float y, float scale) {
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
  this->scale = scale;
  R = 0;
  B = 0;
  G = 0;
}

void Label::setup(float x, float y, float scale, bool timer) {
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
  this->scale = scale;
  R = 0;
  B = 0;
  G = 0;
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
  TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24); //this opens a font style and sets a size

  SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

  SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, str, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

 // SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

  SDL_Rect Message_rect; //create a rect
  Message_rect.x = 0;  //controls the rect's x coordinate 
  Message_rect.y = 0; // controls the rect's y coordinte
  Message_rect.w = 100; // controls the width of the rect
  Message_rect.h = 100; // controls the height of the rect
  x = 0;
  y = 0;
  height= 100;
  width = 100;
  
  drawBox();
  //Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance

  //Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

  //SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
  /*glPushMatrix();
  
  glColor3f(R, G, B); // Text Colour
  glTranslatef(x-length*10, y-10, 0);// *20, y, 0);
  glScalef(scale,scale,scale);
  
  for(int i = 0; i < length; i++) {
    //glutBitmapCharacter(font, str[i]);//Draw character to screen
    glutStrokeCharacter(GLUT_STROKE_ROMAN , str[i]);
  }
   
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//return colours to the full amounts

  glPopMatrix();*/
}

void Label::setTexture(char* filename) {
  Texture = txt::LoadTexture(filename);
  hasTexture = true;
}

void Label::setText(const char* str, int length) {
  for(int i = 0; i < length; ++i)
    this->str[i] = str[i];
   this->length = length;
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

