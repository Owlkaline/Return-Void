#ifndef AlphaOneMount_H
#define AlphaOneMount_H

#include "./Mount.h"

class AlphaOneMount: public Mount {
  public:
    AlphaOneMount();
    ~AlphaOneMount();
       
    void erase();
    void defaults();
    std::string getTexture();
    void individualClean();
    void tick(float x, float y, float deltaTime, float directionX, float directionY, float angle, bool isShooting);

  protected:   
    std::vector<int> cycle;
    std::vector<float> Nx;
    std::vector<float> Ny;
}; 

#endif
