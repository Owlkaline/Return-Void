#include "Level.h"

Level::Level() {
    srand (time(NULL));
    inLevel = false;
    printf("Level Constructed\n");
}

void Level::destroy() {
    inLevel = false;
    //for(unsigned int i = 0; i < enemy.size(); i++) {
    enemy.erase(enemy.begin(), enemy.end());
    printf("\nenemies destroid");
    //}    
}

void Level::setup(GLuint *enemyTexture, float aspectRatio) {
    this->aspectRatio = aspectRatio;
    this->enemyTexture[0] = enemyTexture[0];
    this->enemyTexture[1] = enemyTexture[1];
    crntLevel = -1;
    inLevel = false;
}

std::vector<Enemy*> Level::Tick() {
    switch(crntLevel) {
        case 1:
            Level1();
            break;
    }
    return enemy;
}

void Level::randomSpawn() {

    //int numEnemies = 10 - enemy.size();

        
    for(unsigned int i = 0; i < enemy.size(); i++) {
        if(!enemy[i]->getVisible()) {
            enemy[i]->setSize(0.7 + (random() % 110) / 100.0f); 
            enemy[i]->setX( ((random() % (100 - enemy[i]->getWidth()))));
            enemy[i]->setY( ((random() % (100 - enemy[i]->getHeight())) + 100));
            enemy[i]->setSpeed( (random() % 50) / 100.0f + 0.03f);
            enemy[i]->setMaxHealth( (random() % 8) + 4);
            enemy[i]->setFireRate( (random() % 200) / 100.0f + 0.5);
            enemy[i]->setVisible(true);
           // printf("\ntotal enemy: %d", enemy.size());
        }
    }
}

void Level::Level1() {

    // 100 of Myclass
    //vector<MyClass> myVector( 100, MyClass() );
   // for(unsigned int i = 0; i < enemy.size(); i++) {
    //    if(!enemy[i]->getVisible()) {
     //       enemy.erase(enemy.begin() + i);
    //    }
   // }
    if(!inLevel) {
        for(int i = 0; i < 10; i++) {
            enemy.push_back(new Enemy);
            enemy[i]->setup(enemyTexture, aspectRatio);
                        enemy[i]->setSize(0.7 + (random() % 110) / 100.0f); 
            enemy[i]->setX( ((random() % (100 - enemy[i]->getWidth()))));
            enemy[i]->setY( ((random() % (100 - enemy[i]->getHeight())) + 100));
            enemy[i]->setSpeed( (random() % 50) / 100.0f + 0.03f);
            enemy[i]->setMaxHealth( (random() % 8) + 4);
            enemy[i]->setFireRate( (random() % 200) / 100.0f + 0.5);
            enemy[i]->setVisible(true);
        }
        inLevel = true;
        crntLevel = 1;
    }
    randomSpawn();

} 
