#ifndef GAME_H
#define GAME_H

#include <vector>

#include "../Ships/Ship.h"
#include "./DisplayManager.h"
#include "../Enemies/BasicEnemy.h"
#include "../Namespaces/Collisions.h"
#include "../Enemies/CorruptedStarShip.h"


class Game: public DisplayManager {
  public:
    Game();
    
    void draw();    
    void setup();
    void clean();
    void newWave();
    void restart();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);

  protected:
    void drawCrosshair();
    void drawBackground();
    
    bool isNew; //If Game is new
    
    // Cross Hair
    float lastChX, lastChY, ChX, ChY, ChRadius;
    
    Ship ship;
    GLuint ChTexture; 
    std::vector<Enemy*> enemy;

};

#endif
