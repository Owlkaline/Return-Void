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
        if( (player.getX()+1 >= enemy.getX()+1 && player.getX()+1 <= ( enemy.getX()+1 + enemy.getWidth()-1 ) ) || 
          ((player.getX()+1 + player.getWidth()-1) >= enemy.getX()+1 && ( player.getX()+1 + enemy.getWidth()-1 ) <= ( enemy.getX()+1 + enemy.getWidth()-1 )) ) {
               
           if( (player.getY()+1 >= enemy.getY()+1 && player.getY()+1 <= ( enemy.getY()+1 + enemy.getHeight()-1 ) ) || 
              ((player.getY()+1 + player.getHeight()-1) >= enemy.getY()+1 && ( player.getY()+1 + enemy.getHeight()-1 ) <= ( enemy.getY()+1 + enemy.getHeight()-1 )) ) {
                   
               enemy.looseHealth(1);
               player.reset(); 
           }
        }
        for(int i = 0; i < 20; ++i) {
            if(player.getBulletVisible(i)) {
                if( (player.getBulletX(i) >= enemy.getX()+1 && player.getBulletX(i) <= ( enemy.getX()+1 + enemy.getWidth()-1 ) ) || 
                 ((player.getBulletX(i) + player.getBulletWidth(i)) >= enemy.getX()+1 && ( player.getBulletX(i) + enemy.getWidth()-1 ) <= ( enemy.getX()+1 + enemy.getWidth()-1 )) ) {
               
                    if( (player.getBulletY(i) >= enemy.getY()+1 && player.getBulletY(i) <= ( enemy.getY()+1 + enemy.getHeight()-1 ) ) || 
                      ((player.getBulletY(i) + player.getBulletHeight(i)) >= enemy.getY()+1 && ( player.getBulletY(i) + enemy.getHeight()-1 ) <= ( enemy.getY()+1 + enemy.getHeight()-1 )) ) {
                       
                       player.setBulletVisible(false, i);
                       enemy.looseHealth(1);
                    }
                } 
            }
        }
    }
}

//draw string
/*void Game::drawString(int PosX, int PosY, float R, float G, float B, std::string str) {
        glColor3f(R, G, B); // Text Colour


        glRasterPos2i(PosX, PosY); //coordinates of text
        glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //colour blue
        static std::string s = str;
        void * font = GLUT_BITMAP_HELVETICA_18;//set font http://www.opengl.org/documentation/specs/glut/spec3/node76.html#SECTION000111000000000000000
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)//draw to screen
            {
                char c = *i;
                glutBitmapCharacter(font, c);
            }
    }
*/
void Game::drawHub() {
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        //glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(0, 100, 0.0);
       // glTexCoord2f(1.0f, 0.0f);
        glVertex3f(100, 100, 0.0);
       // glTexCoord2f(1.0f, 1.0f);
        glVertex3f(100, 92, 0.0);
      //  glTexCoord2f(0.0f, 1.0f);
        glVertex3f(0, 92, 0.0);
        
        
        //Health Bar
        glColor3f(1.0f, 0.0f, 0.0f);
        
        glVertex3f(79, 97, 0.0);
       // glTexCoord2f(1.0f, 0.0f);
        glVertex3f(79 + 20 * (player.getHealth()/5.0f), 97, 0.0);
       // glTexCoord2f(1.0f, 1.0f);
        glVertex3f(79 + 20 * (player.getHealth()/5.0f), 95, 0.0);
      //  glTexCoord2f(0.0f, 1.0f);
        glVertex3f(79, 95, 0.0);
        
        //Health Bar Border
        glColor3f(0.8f, 0.0f, 1.0f);
        
        glVertex3f(78.5f, 98.0f, 0.0);
        glVertex3f(99.5f, 98.0f, 0.0);
        glVertex3f(99.5f, 97, 0.0);
        glVertex3f(78.5f, 97, 0.0);
        
        glVertex3f(78.5f, 95.0f, 0.0);
        glVertex3f(99.5f, 95.0f, 0.0);
        glVertex3f(99.5f, 94, 0.0);
        glVertex3f(78.5f, 94, 0.0);
        
        glVertex3f(99.0f, 97.0f, 0.0);
        glVertex3f(99.5f, 97.0f, 0.0);
        glVertex3f(99.5f, 95, 0.0);
        glVertex3f(99.0f, 95, 0.0);
        
        glVertex3f(78.5f, 97.0f, 0.0);
        glVertex3f(79.0f, 97.0f, 0.0);
        glVertex3f(79.0f, 95, 0.0);
        glVertex3f(78.5f, 95, 0.0);
        
        //Black bars in health bar
        glColor3f(0.0f, 0.0f, 0.0f);
        
        for(int i = 0; i < 4; ++i) {
            glVertex3f(78.8f + 20 * ((i+1)/5.0f), 97.0f, 0.0);
            glVertex3f(79 + 20 * ((i+1)/5.0f), 97.0f, 0.0);
            glVertex3f(79 + 20 * ((i+1)/5.0f), 95, 0.0);
            glVertex3f(78.8f + 20 * ((i+1)/5.0f), 95, 0.0);
        }
        
       // drawString(50, 50, 1.0f, 0, 0, "Score: 5396");
        
    glEnd();
    
}

void Game::draw() {
    if(enemy.getVisible())
        enemy.draw();
        
    drawHub();
    if(player.getHealth() > 0) {
        player.draw();
        collisions();
    }
}
