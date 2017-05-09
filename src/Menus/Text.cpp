#include "../../include/Menus/Text.h"

void Text::draw() {
  for(unsigned int i = 0; i < text.length(); ++i) {
    if(text[i] != ' ' && text[i] != ',' && text[i] != '.' && text[i] != ':') {
      glEnable(GL_TEXTURE_2D);
      float offsetx = 0;
      float offsety = 0;
    
      std::string str = "./Textures/Menu/Letters/";
      str += text[i];
      str += ".png";

      switch(text[i]) {
        case 'A':
        case 'B':
        //case 'C':
        case 'D':
        case 'E': 
        case 'F':
        case 'G':
       // case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'N':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
          offsetx = -15;
          offsety = 10;
          break;
        case 'C': offsetx = 15; break;
        case 'p': offsety = -5; break;
      }
      width = 80;
      glBindTexture(GL_TEXTURE_2D, getLetter(text[i]));
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x-width/2 + 30*i + offsetx, y+height/2+offsety, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x+width/2 + 30*i + offsetx, y+height/2+offsety, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x+width/2 + 30*i + offsetx, y-height/2+offsety, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x-width/2 + 30*i + offsetx, y-height/2+offsety, 0.0);
      glEnd();
      glDisable(GL_TEXTURE_2D);
    } 
  }
}

void Text::setup(float x, float y, char* text) { 
  width = 80;
  height = 95;
  this->x = x;
  this->y = y;
  this->text = text;
  this->x = x - this->text.length()/2 * width/2;
}
