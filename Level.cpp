#include "Level.h"

Level::Level() {
    srand (time(NULL));
    inLevel = false;
    printf("Level Constructed\n");
}

void Level::setup() {
    crntLevel = -1;
    inLevel = false;
}

void Level::Tick(Enemy *enemy) {
    switch(crntLevel) {
        case 1:
            Level1(enemy);
            break;
    }
}

void Level::randomSpawn(Enemy *enemy, int i) {
        enemy[i].setSize(0.7 + (random() % 110) / 100.0f); 
        enemy[i].setX( ((random() % (100 - enemy[i].getWidth()))));
        enemy[i].setY( ((random() % (100 - enemy[i].getHeight())) + 100));
        enemy[i].setSpeed( (random() % 50) / 100.0f + 0.03f);
        enemy[i].setMaxHealth( (random() % 8) + 4);
        enemy[i].setFireRate( (random() % 200) / 100.0f + 0.5);
        enemy[i].setVisible(true);
}

void Level::Level1(Enemy *enemy) {
    if(!inLevel) {
        for(int i = 0; i < 10; ++i) {
            randomSpawn(enemy, i);
        }
        crntLevel = 1;
        inLevel = true;
    } else {
    
        for(int i = 0; i < 10; ++i) {
            if(!enemy[i].getVisible()) {
                randomSpawn(enemy, i);
            }
        }
    } 
} 
