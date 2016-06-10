#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <vector>

#include "./Enemy.h"
#include "./Ship.h"


namespace Collisions{

    void detect(Ship* ship, std::vector<Enemy*>);

    int getQuadrant(float x, float y);
}

#endif

