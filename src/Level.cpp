#include "../include/Level.h"

Level::Level() {
    srand (time(NULL));
    inLevel = false;
    printf("Level Constructed\n");
}

void Level::destroy() {
    inLevel = false;
    BaseEnemies.erase(BaseEnemies.begin(), BaseEnemies.end());
}

void Level::setup(GLuint *enemyTextures, GLuint *enemyBulletTextures, GLuint *powerupTextures, float aspectRatio) {
    this->aspectRatio = aspectRatio;
    for(unsigned int i = 0; i < sizeof(enemyTextures)/sizeof(enemyTextures[0]); ++i) {
        this->enemyTextures[i] = enemyTextures[i];
    }
    this->enemyBulletTextures[0] = enemyBulletTextures[0];
    this->powerupTextures[0] = powerupTextures[0];
    this->powerupTextures[1] = powerupTextures[1];
    this->powerupTextures[2] = powerupTextures[2];

    crntLevel = -1;
    inLevel = false;
}

void Level::Tick() {
    switch(crntLevel) {
        case 1:
            Level1();
            break;
    }
}

void Level::newDrop(float x, float y) {
    powerups.push_back(new Powerups);
    int i = powerups.size()-1;
    switch(item) {
        case Money:
            powerups[i]->spawnMoney(x, y, powerupTextures[0]);
            break;
        case Shield:
            powerups[i]->spawnShield(x, y, powerupTextures[1]);
            break;
        case Bomb:
            powerups[i]->spawnMoney(x, y, powerupTextures[2]);
            break;
    }
}

void Level::randomSpawn() {

    for(unsigned int i = 0; i < BaseEnemies.size(); i++) {
        if(!BaseEnemies[i]->getVisible()) {
            item = (ItemDrop)BaseEnemies[i]->Drops();
            newDrop(BaseEnemies[i]->getX(), BaseEnemies[i]->getY());
            float x = ( rand() % (int)(100.0f-BaseEnemies[i]->getWidth()/2.0f) + BaseEnemies[i]->getWidth()/2.0f);
            float y = ( ((rand() % 100) + 100) );
            float speed = ( (rand() % 50) / 100.0f + 0.03f);
            int maxHealth = ( (rand() % 5) + 2);
            int fireRate = (250 + rand()%100);
            BaseEnemies[i]->spawn(x, y, speed, maxHealth, fireRate);
        }
    }
}

void Level::Level1() {
    if(!inLevel) {
        for(int i = 0; i < 7; i++) {
           if (i % 3 == 0) {
              BaseEnemies.push_back(new BasicEnemy);
           } else {
              BaseEnemies.push_back(new BaseEnemy);
           }

           BaseEnemies[i]->setup(enemyTextures, enemyBulletTextures, aspectRatio);
        }


        inLevel = true;
        crntLevel = 1;
    }
    randomSpawn();
}
