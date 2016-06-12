#ifndef COLLISIONS_H
#define COLLISIONS_H

#define MAXLEVEL 1

#include <vector>

#include "../Enemies/Enemy.h"
#include "../Ships/Ship.h"


namespace Collisions{
    
    void detect(Ship* ship, std::vector<Enemy*>);

    int getQuadrant(float x, float y, int level);
    
    void drawHitBoxes(Ship* ship, std::vector<Enemy*> enemy);
    
    void drawBox(float x, float y, float width, float height);
    void drawQuadTree();
}

#endif

