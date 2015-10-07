#include "Game.h"

Game::Game() {
    srand (time(NULL));
    printf("Game Constructed\n");
}

void Game::setup(GLuint *textures) {
    score = 0;
    player.setup(textures);
    enemy.setup(textures[4], textures[5]);
    
    //Score
    texture[0] = textures[14];
    texture[1] = textures[15];
    texture[2] = textures[16];
    texture[3] = textures[17];
    texture[4] = textures[18];
    texture[5] = textures[19];
    texture[6] = textures[20];
    texture[7] = textures[21];
    texture[8] = textures[22];
    texture[9] = textures[23];
    
    //Top Bar
    texture[10] = textures[12];
    
    //Health Bar
    texture[11] = textures[13];
    
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
    
    //Fire player weapon
    if(keyState[32] == BUTTON_DOWN) { //Space Bar
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
                       score += enemy.looseHealth(1);
                    }
                } 
            }
        }
    }
}

//draw string
void Game::drawChar(int PosX, int PosY, float R, float G, float B, char str[25], int length) {
    glColor3f(R, G, B); // Text Colour
    glRasterPos2i(PosX, PosY); //coordinates of text
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //colour blue
    
    void * font = GLUT_BITMAP_HELVETICA_18;//set font http://www.opengl.org/documentation/specs/glut/spec3/node76.html#SECTION000111000000000000000
       
     for(int i = 0; i < length; i++) {
             glutBitmapCharacter(font, str[i]);
     }  
     glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    
}

void Game::drawStars() {
    
    int x, y;
    glBegin(GL_POINTS);
	for(int i = 0; i < 100; i++)
	{
	    glColor3f( (rand()%100) / 100.0f, (rand()%100) / 100.0f, (rand()%100) / 100.0f);
	    x = rand() % 100;
        y = rand() % 100;
		glVertex2i(x,y);
		glVertex2i(x+0.1,y);
		glVertex2i(x,y+0.1);
		glVertex2i(x+0.1,y+0.1);
	}
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
	
}

void Game::drawScore() { 
    glEnable(GL_TEXTURE_2D);
    
    for(int i = 0; i < 10; ++i) {
    int num;
    switch(i) {
        case 9:
            num = score % 10;
            break;
        case 8:
            num = score / 10 % 10;
            break;
        case 7:
            num = score / 100 % 10;
            break;
        case 6:
            num = score / 1000 % 10;
            break;
        case 5:
            num = score / 10000 % 10;
            break;
        case 4:
            num = score / 100000 % 10;
            break;
        case 3:
            num = score / 1000000 % 10;
            break;
        case 2:
            num = score / 10000000 % 10;
            break;
        case 1:
            num = score / 100000000 % 10;
            break;
        case 0:
            num = score / 1000000000 % 10;
            break;
    }
	glBindTexture(GL_TEXTURE_2D, texture[num]);
	//Score 
	glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(100/3.0f + (i*3), 99, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(100/3.0f + 3 + (i*3), 99, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(100/3.0f + 3 + (i*3), 93, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(100/3.0f + (i*3), 93, 0.0);
    glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}

void Game::drawHud() {

    drawStars();
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[10]);
	
	//Top Bar    
	glBegin(GL_QUADS);
      glTexCoord2f(0.1f, 0.0f); 
      glVertex3f(0, 100, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(100, 100, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(100, 92, 0.0);
      glTexCoord2f(0.1f, 1.0f);
      glVertex3f(0, 92, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, texture[1]);
	glColor3f(1.0f, 0.0f, 0.0f);
    
    //Health Bar  
    glBegin(GL_QUADS);
      glVertex3f(79, 97, 0.0);
      //glTexCoord2f(1.0f, 0.0f);
      glVertex3f(79 + 20 * (player.getHealth()/5.0f), 97, 0.0);
      //glTexCoord2f(1.0f, 1.0f);
      glVertex3f(79 + 20 * (player.getHealth()/5.0f), 95, 0.0);
     // glTexCoord2f(0.0f, 1.0f);
      glVertex3f(79, 95, 0.0);
    glEnd();   
    
    //Health Bar Border      
    glBegin(GL_QUADS);  
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
    glColor3f(1.0f, 1.0f, 1.0f);
    glDisable(GL_TEXTURE_2D);
    
}

void Game::draw() {

    if(enemy.getVisible())
        enemy.draw();        
   
    if(player.getHealth() > 0) {
        player.draw();
        collisions();
    }
    
    drawHud();
    drawScore();
    //drawChar(50 ,98, 0, 1, 0, "Score", 5);
}
