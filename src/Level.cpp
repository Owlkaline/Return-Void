#include "../include/Level.h"

Level::Level() {
    srand (time(NULL));
    inLevel = false;
    printf("Level Constructed\n");
}

void Level::destroy() {
    inLevel = false;
    //for(unsigned int i = 0; i < BaseEnemies.size(); i++) {
    BaseEnemies.erase(BaseEnemies.begin(), BaseEnemies.end());
    BasicEnemies.erase(BasicEnemies.begin(), BasicEnemies.end());
    //printf("\nenemies destroid");
    //}    
}

void Level::setup(GLuint *enemyTextures, GLuint *enemyBulletTextures, float aspectRatio) {
    this->aspectRatio = aspectRatio;
    for(unsigned int i = 0; i < sizeof(enemyTextures)/sizeof(enemyTextures[0]); ++i) {
        this->enemyTextures[i] = enemyTextures[i];
    }
    this->enemyBulletTextures[0] = enemyBulletTextures[0];
    //this->BaseEnemiesTexture[1] = BaseEnemiesTexture[1];
    crntLevel = -1;
    inLevel = false;
}

void Level::Tick() {
    switch(crntLevel) {
        case 1:
            Level1();
            break;
    }
    //return BaseEnemies;
}

void Level::randomSpawn() {
    
    for(unsigned int i = 0; i < BaseEnemies.size(); i++) {
        if(!BaseEnemies[i]->getVisible()) {
            float x = ( rand() % (100-BaseEnemies[i]->getWidth()/2) + BaseEnemies[i]->getWidth()/2);
            float y = ( ((rand() % 100) + 100) );
            float speed = ( (rand() % 50) / 100.0f + 0.03f);
            int maxHealth = ( (rand() % 8) + 4);
            int fireRate = (250 + rand()%100);
            BaseEnemies[i]->spawn(x, y, speed, maxHealth, fireRate);
           // printf("\ntotal BaseEnemies: %d", BaseEnemies.size());
        }
    }
    
    for(unsigned int i = 0; i < BasicEnemies.size(); i++) {
        if(!BasicEnemies[i]->getVisible()) {
            float x = ( rand() % (100-BasicEnemies[i]->getWidth()/2) + BasicEnemies[i]->getWidth()/2);
            float y = ( ((rand() % 100) + 100) );
            float speed = ( (rand() % 25) / 100.0f + 0.02f);
            int fireRate = (20 + rand()%40);
            BasicEnemies[i]->spawn(x, y, speed, fireRate);
           // printf("\ntotal BaseEnemies: %d", BaseEnemies.size());
        }
    }
        
    
   /* for(unsigned int i = 0; i < BasicEnemies.size(); i++) {
        if(!BasicEnemies[i]->getVisible()) {
            float x = ( rand() % (100-BasicEnemies[i]->getWidth()/2) + BasicEnemies[i]->getWidth()/2);
            float y = ( ((rand() % 100) + 100) );
            float speed = ( (rand() % 50) / 100.0f + 0.03f);
            int fireRate = (50);
            BasicEnemies[i]->spawn(50, 50, speed, fireRate);
           // printf("\ntotal BaseEnemies: %d", BaseEnemies.size());
        }
    }*/
}

void Level::Level1() {

    // 100 of Myclass
    //vector<MyClass> myVector( 100, MyClass() );
   // for(unsigned int i = 0; i < BaseEnemies.size(); i++) {
    //    if(!BaseEnemies[i]->getVisible()) {
     //       BaseEnemies.erase(BaseEnemies.begin() + i);
    //    }
   // }
    if(!inLevel) {
        for(int i = 0; i < 7; i++) {   
            BaseEnemies.push_back(new EnemyBase);
            BaseEnemies[i]->setup(enemyTextures, enemyBulletTextures, aspectRatio); 
            
            if(i < 3) {  
                BasicEnemies.push_back(new BasicEnemy);
                BasicEnemies[i]->setup(enemyTextures, enemyBulletTextures, aspectRatio);       
            }
        }
        inLevel = true;
        crntLevel = 1;
    }
    randomSpawn();

} 
