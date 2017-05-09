#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string> 

#include "../defines.h"

#include "../Menus/Label.h"
#include "../Menus/Button.h"

#include "./DisplayManager.h"

class Menu: public DisplayManager {
  public:
    virtual void setup()=0;
    virtual void restart()=0;
    virtual void drawAfter() {  }
    virtual void update(float mX, float mY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState)=0;
    
    float getX() { return x; }
    float getY() { return y; }
    float getWidth() { return width; }
    float getHeight() { return height; }
    
    virtual void clean() { 
      buttons.clear(); lb.clear();
      buttons.erase(buttons.begin(), buttons.end());
      lb.erase(lb.begin(), lb.end());
    }
                 
    void draw() {
      drawBackground();
            for(unsigned int i = 0; i < lb.size(); ++i) 
        lb[i]->draw();
      for(unsigned int i = 0; i < buttons.size(); ++i)
        buttons[i]->draw();
      drawAfter();
    }
    
  protected:
    virtual void drawBackground() {
      // Background
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, background);
 
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0, SPACE_Y_RESOLUTION, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(SPACE_X_RESOLUTION, SPACE_Y_RESOLUTION, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(SPACE_X_RESOLUTION, 0, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0, 0, 0.0);
      glEnd();      
      glDisable(GL_TEXTURE_2D);
  
      // Black Box in center
      glColor4f(0.0, 0.0, 0.0f, 0.5f);
      glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f((SPACE_X_RESOLUTION/4), (SPACE_Y_RESOLUTION/6) * 4, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f((SPACE_X_RESOLUTION/4)*3, (SPACE_Y_RESOLUTION/6) * 4, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f((SPACE_X_RESOLUTION/4)*3, 0, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(SPACE_X_RESOLUTION/4, 0, 0.0);
      glEnd();
      glColor4f(1.0, 1.0, 1.0f, 1.0f);
    }
    
    float x, y, width, height;
    
    std::vector<Label*> lb;
    std::vector<Button*> buttons;    
    
    GLuint background;
};

#endif
