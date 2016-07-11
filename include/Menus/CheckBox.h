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
    float width, height, x, y;
    bool isChecked;
    GLuint Texture[2];
};

#endif
