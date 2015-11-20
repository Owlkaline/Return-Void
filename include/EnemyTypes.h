#ifndef ENEMYTYPES_H
#define ENEMYTYPES_H

#include "EnemyBase.h"

class BasicEnemy: public EnemyBase {
    public:
        void setup(GLuint *enemyTextures, GLuint *enemyBulletTextures,  float aspectRatio);
        void spawn(float x, float y, float speed, float fireRate);
};


#endif
