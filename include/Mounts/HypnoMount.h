#ifndef HYPNOMOUNT_H
#define HYPNOMOUNT_H

#include "./Mount.h"

class HypnoMount: public Mount {
  public:
    HypnoMount();
    ~HypnoMount();
      
    void setLeft();
    void defaults();
    std::string getTexture();
    
  protected:
};

#endif
