#ifndef GAME_H
#define GAME_H

#include <vector>

#include "./DisplayManager.h"
#include "../Ships/Ship.h"
#include "../Enemies/BasicEnemy.h"
#include "../Enemies/CorruptedStarShip.h"
#include "../Namespaces/Collisions.h"

class Game: public DisplayManager {
  public:
    Game();
    
    void draw();
    void update(float mX, float mY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState);
    void setup();
    void restart();
    void clean();
    
    void newWave();
  protected:
    void drawBackground();
    void drawCrosshair();
    Ship ship;
    std::vector<Enemy*> enemy;
    bool isNew;
    // Cross Hair
    float lastChX, lastChY, ChX, ChY, ChRadius;
    GLuint ChTexture;
};

#endif
