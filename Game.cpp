#include "Game.h"

Game::Game() {
    srand (time(NULL));
    crntTime = clock();
    printf("Game Constructed\n");
}

void Game::setup() {
    level.setup();
    score = 0;
    GLuint playerTextures[5];
    playerTextures[0] = LoadTexture( "Textures/Game/Ship.bmp" );
    playerTextures[1] = LoadTexture( "Textures/Game/ShipLeft.bmp" );
    playerTextures[2] = LoadTexture( "Textures/Game/ShipRight.bmp" );
    playerTextures[3] = LoadTexture( "Textures/Game/PlayerBullet.bmp" );    
    player.setup(playerTextures);
    
    GLuint enemyTexture[2];
    enemyTexture[0] = LoadTexture( "Textures/Game/Enemy.bmp" ); 
    enemyTexture[1] = LoadTexture( "Textures/Game/EnemyBullet.bmp" ); 
    //default
    for(int i = 0; i < 10; ++i) {
        enemy[i].setup(enemyTexture);
        enemy[i].setX(i*10);
    }
    //Score
    texture[0] = LoadTexture( "Textures/Score/Zero.bmp" );
    texture[1] = LoadTexture( "Textures/Score/One.bmp" );
    texture[2] = LoadTexture( "Textures/Score/Two.bmp" );
    texture[3] = LoadTexture( "Textures/Score/Three.bmp" );
    texture[4] = LoadTexture( "Textures/Score/Four.bmp" );
    texture[5] = LoadTexture( "Textures/Score/Five.bmp" );
    texture[6] = LoadTexture( "Textures/Score/Six.bmp" );
    texture[7] = LoadTexture( "Textures/Score/Seven.bmp" );
    texture[8] = LoadTexture( "Textures/Score/Eight.bmp" );
    texture[9] = LoadTexture( "Textures/Score/Nine.bmp" );
    
    //Top Bar
    texture[10] = LoadTexture( "Textures/Hud/TopBar.bmp" );

    //Health Bar
    texture[11] = LoadTexture( "Textures/Hud/HealthBar.bmp" );
    level.Level1(enemy);
    printf("Game setup\n");
}

void Game::destroy() {
    player.destroy();
    
    for(int i = 0; i < 1; ++i) {
        enemy[i].destroy();
    }
}
  
void Game::keyPress(unsigned char* keyState, unsigned char* prevKeyState) {
    
    if(player.getVisible()) {
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
                printf("Space Bar pressed\n");
                shootTime = crntTime;
                player.fire();
            } else {
                printf("%li\n", crntTime - shootTime);
                if( (crntTime - shootTime) > 3000) {
                    shootTime = crntTime;
                    player.fire();
                }
            }
        }
        prevKeyState[32] = keyState[32];
            
        if(keyState[(unsigned char)'a'] == BUTTON_UP && keyState[(unsigned char)'d'] == BUTTON_UP) {
            player.stationaryImage();
        }
    }
}

void Game::collisions() {   
    for(int i = 0; i < 10; ++i) {
        if(enemy[i].getVisible() && player.getVisible()) {
            if( (player.getX()+1 >= enemy[i].getX()+1 && player.getX()+1 <= ( enemy[i].getX()+1 + enemy[i].getWidth()-1 ) ) || 
              ( (player.getX()+1 + player.getWidth()-1) >= enemy[i].getX()+1 && ( player.getX()+1 + enemy[i].getWidth()-1 ) <= ( enemy[i].getX()+1 + enemy[i].getWidth()-1 )) ) {
                   
               if( (player.getY()+1 >= enemy[i].getY()+1 && player.getY()+1 <= ( enemy[i].getY()+1 + enemy[i].getHeight()-1 ) ) || 
                 ( (player.getY()+1 + player.getHeight()-1) >= enemy[i].getY()+1 && ( player.getY()+1 + enemy[i].getHeight()-1 ) <= ( enemy[i].getY()+1 + enemy[i].getHeight()-1 )) ) {
                       
                   enemy[i].looseHealth(2);
                   player.takeHealth(2);
                   player.respawn(50, 5); 
               }
            }
        }
          
        if(enemy[i].getVisible()) {  
            for(int j = 0; j < 10; ++j) {
                if(player.getBulletVisible(j)) {
                    if( (player.getBulletX(j) >= enemy[i].getX()+1 && player.getBulletX(j) <= ( enemy[i].getX()+1 + enemy[i].getWidth()-1 ) ) || 
                      ( (player.getBulletX(j) + player.getBulletWidth(j)) >= enemy[i].getX()+1 && ( player.getBulletX(j) + enemy[i].getWidth()-1 ) <= ( enemy[i].getX()+1 + enemy[i].getWidth()-1 )) ) {
                   
                        if( (player.getBulletY(j) >= enemy[i].getY()+1 && player.getBulletY(j) <= ( enemy[i].getY()+1 + enemy[i].getHeight()-1 ) ) || 
                          ( (player.getBulletY(j) + player.getBulletHeight(j)) >= enemy[i].getY()+1 && ( player.getBulletY(j) + enemy[i].getHeight()-1 ) <= ( enemy[i].getY()+1 + enemy[i].getHeight()-1 )) ) {
                           
                           player.setBulletVisible(false, j);
                           score += enemy[i].looseHealth(1);
                        }
                    } 
                }
            }
        }
        
        if(player.getVisible() && enemy[i].getBulletVisible()) {
            if( (player.getX() >= enemy[i].getBulletX() && player.getX() <= ( enemy[i].getBulletX() + enemy[i].getBulletWidth() ) ) || 
              ( (player.getX() + player.getWidth()) >= enemy[i].getBulletX() && ( player.getX() + enemy[i].getBulletWidth() ) <= ( enemy[i].getBulletX() + enemy[i].getBulletWidth() )) ) {
              
                if( (player.getY()-1 >= enemy[i].getBulletY() && player.getY()-1 <= ( enemy[i].getBulletY() + enemy[i].getBulletHeight()-1 ) ) || 
                  ( (player.getY() + player.getHeight()-1) >= enemy[i].getBulletY() && ( player.getY() + enemy[i].getBulletHeight()-1 ) <= ( enemy[i].getBulletY() + enemy[i].getBulletHeight() )) ) {
                    enemy[i].setBulletVisible(false);
                    player.takeHealth(1);
                    player.respawn(50, 5);
                    
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
    crntTime = clock();
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

bool Game::Tick(unsigned char* keyState, unsigned char* prevKeyState) {
    level.Tick(enemy);
    keyPress(keyState, prevKeyState);
    player.Tick();
    collisions();
    
    for(int i = 0; i < 10; ++i) {
        if(enemy[i].getVisible())
            enemy[i].Tick(player.getX()+player.getWidth()/2, player.getY()+player.getHeight()/2);
    }
    
    draw();
    
    if(player.getHealth() <= 0)  
        return false;
    
    return true;
}

void Game::draw() {
    for(int i = 0; i < 10; ++i) {
        if(enemy[i].getVisible())
            enemy[i].draw(); 
        if(enemy[i].getBulletVisible()) {
            enemy[i].drawBullets();
        }   
    }
    
    if(player.getHealth() > 0) {
        player.draw();
    }
    
    drawHud();
    drawScore();
}


GLuint Game::LoadTexture( const char * filename ) {
    GLuint textures;
 
    int width, height;

    unsigned char * data;

    FILE * file;

    file = fopen( filename, "rb" );
  
    if ( file == NULL ) return 0;
    // printf("file opened\n");
    width = 1024;
    height = 1024;
    data = (unsigned char *)malloc( width * height * 4 );
    //int size = fseek(file,);
    fseek(file,3,SEEK_CUR); // if we go forward 3 bytes then the BMP color
                            // order is BGRA.
                            // Without an fseek, the order is GRAB
    fread( data, 1, width * height * 4, file );
    fclose( file );
 
     glGenTextures(1, &textures);
     glBindTexture(GL_TEXTURE_2D, textures);
  
     glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);
     free( data );
     return textures;
}
