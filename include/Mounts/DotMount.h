#ifndef DOTMOUNT_H
#define DOTMOUNT_H

#include "./Mount.h"

class DotMount: public Mount {
  public:
    DotMount();
    ~DotMount();
      
    void defaults();
    std::string getTexture();
    void draw(GraphicsHandler *graphics) {      
      for(unsigned int i = 0; i < bullets.size(); ++i)
        bullets[i]->draw(graphics);
    }
    
  protected:
};

#endif
