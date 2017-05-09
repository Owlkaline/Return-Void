#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "../Namespaces/LoadTexture.h"

class CheckBox {
  public:
    ~CheckBox();
  
    void draw();
    void setup(float x, float y);

    void check();
    void uncheck();
    
    bool getChecked();
  protected:    
    bool isChecked;
    
    float width, height, x, y;
    
    GLuint Texture[2];
};

#endif
