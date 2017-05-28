#include "../../include/Menus/Label.h"

Label::Label() {

}

Label::~Label() {
  texture = "";
}

void Label::draw(GraphicsHandler *graphics) {
  if(visible) {
    if(isFilled) {
     /* glColor3f(fillR, fillG, fillB);
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
      
      // Button example
      drawQuad(x, -width, y, height, UP);
      
      */
    }
    
    if(hasTexture) {  
    // if(disabled)
     //   glColor4f(1.0, 1.0, 1.0, 0.5);
      /*
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
      glDisable(GL_TEXTURE_2D);*/
      graphics->drawObject(glm::vec2(x, y), glm::vec2(width, height), texture);
    } else {
      if(isTimed) {
        if(ticks > 0)
          graphics->drawText(str, glm::vec2(x,y), scale, colour, "DarkCrystal");
      } else {
        //text.draw();
        //drawChar();
        graphics->drawText(str, glm::vec2(x,y), scale, colour, "DarkCrystal");
      }
    }
    if(hasBorder)
      drawBox(graphics);
  }
}

void Label::clean() {

}

void Label::setup(float x, float y, float width, float height, std::string filename) {
  texture = filename;
  hasTexture = true;
  isTimed = false;
  hasBorder = false;
  isFilled = false;
  visible = true;
  disabled = false;
  ticks = 0;
  this->x = x;
  this->y = y;
  this->width = width;
  this->height = height;
  this->scale = 0;
  colour = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Label::setup(float x, float y, float scale) {
  hasTexture = false;
  isTimed = false;
  hasBorder = false;
  isFilled = false;
  visible = true;
  disabled = false;
  ticks = 0;
  this->x = x;
  this->y = y;
  this->scale = scale;
  this->colour = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Label::setup(float x, float y, float scale, std::string text) {
  setup(x, y, scale);
  this->str = text;
}

void Label::setup(float x, float y, float scale, glm::vec3 colour, std::string text) {
  setup(x, y, scale, text);
  this->colour = colour;
}

void Label::setup(float x, float y, float scale, bool timer) {
  setup(x, y, scale);
  isTimed = timer;
}

void Label::update(float deltaTime) {
    if(isTimed) {
      ticks-=1*deltaTime;
      if(ticks <= 0)
        ticks = 0;
    } 
}

void Label::setTexture(std::string filename) {
  texture = filename;
  hasTexture = true;
}

void Label::setText(std::string str) {
   this->str = str;
}

void Label::setTimer(int time) {
  ticks = time;
}

void Label::setColour(float R, float G, float B) {
  colour = glm::vec3(R,G,B);
}

void Label::drawBox(GraphicsHandler *graphics) {
  float border = 5;
  /*glColor3f(0.0, 0.0, 0.0);
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
  glColor3f(1.0, 1.0, 1.0);*/
  graphics->useShader("basic");
  graphics->drawObject(glm::vec2(x+border/2, y), glm::vec2(width, height), "Edge");
  graphics->drawObject(glm::vec2(x-border/2, y), glm::vec2(width, height), "Edge");
  graphics->drawObject(glm::vec2(x, y-border/2), glm::vec2(width, height), "Edge");
  graphics->drawObject(glm::vec2(x, y+border/2), glm::vec2(width, height), "Edge");
}

