#include "Game.h"

Game::Game() {
    printf("Game Constructed\n");
}

void Game::setup(GLuint *textures) {
    player.setup(textures);
    enemy.setup(textures[4], textures[5]);
    printf("Game setup\n");
}

void Game::destroy() {
    player.destroy();
    enemy.destroy();
}
  
void Game::keyPress(unsigned char* keyState, unsigned char* prevKeyState) {
    if(keyState[(unsigned char)'a'] == BUTTON_DOWN) {
        player.moveLeft();
        player.leftImage();
    }
    if(keyState[(unsigned char)'d'] == BUTTON_DOWN) {
        player.moveRight();
        player.rightImage();
    }
    if(keyState[(unsigned char)'w'] == BUTTON_DOWN)
        player.moveUp();
    if(keyState[(unsigned char)'s'] == BUTTON_DOWN)
        player.moveDown();
    if(keyState[32] == BUTTON_DOWN) {
        if(prevKeyState[32] != BUTTON_DOWN) {
            player.fire();
        }
    }
    prevKeyState[32] = keyState[32];
        
    if(keyState[(unsigned char)'a'] == BUTTON_UP && keyState[(unsigned char)'d'] == BUTTON_UP) {
        player.stationaryImage();
    }
}

void Game::collisions() {   
    if(enemy.getVisible()) {
        if( (player.getX() >= enemy.getX() && player.getX() <= ( enemy.getX() + enemy.getWidth() ) ) || 
          ((player.getX() + player.getWidth()) >= enemy.getX() && ( player.getX() + enemy.getWidth() ) <= ( enemy.getX() + enemy.getWidth() )) ) {
               
           if( (player.getY() >= enemy.getY() && player.getY() <= ( enemy.getY() + enemy.getHeight() ) ) || 
              ((player.getY() + player.getHeight()) >= enemy.getY() && ( player.getY() + enemy.getHeight() ) <= ( enemy.getY() + enemy.getHeight() )) ) {
                   
               enemy.looseHealth(10);
               player.reset(); 
           }
        }
        for(int i = 0; i < 20; ++i) {
            if(player.getBulletVisible(i)) {
                if( (player.getBulletX(i) >= enemy.getX() && player.getBulletX(i) <= ( enemy.getX() + enemy.getWidth() ) ) || 
                 ((player.getBulletX(i) + player.getBulletWidth(i)) >= enemy.getX() && ( player.getBulletX(i) + enemy.getWidth() ) <= ( enemy.getX() + enemy.getWidth() )) ) {
               
                    if( (player.getBulletY(i) >= enemy.getY() && player.getBulletY(i) <= ( enemy.getY() + enemy.getHeight() ) ) || 
                      ((player.getBulletY(i) + player.getBulletHeight(i)) >= enemy.getY() && ( player.getBulletY(i) + enemy.getHeight() ) <= ( enemy.getY() + enemy.getHeight() )) ) {
                       
                       player.setBulletVisible(false, i);
                       enemy.looseHealth(1);
                    }
                } 
            }
        }
    }
}

void Game::drawHub() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        //glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(0, 100, 0.0);
       // glTexCoord2f(1.0f, 0.0f);
        glVertex3f(100, 100, 0.0);
       // glTexCoord2f(1.0f, 1.0f);
        glVertex3f(100, 90, 0.0);
      //  glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0, 90, 0.0);
    glEnd();
    
}

void Game::draw() {
    if(enemy.getVisible())
        enemy.draw();
    player.draw();
    drawHub();
    collisions();
}
