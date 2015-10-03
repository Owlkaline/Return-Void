#include "Game.h"

Game::Game() {
    /*GLuint texture[4];
    
    texture[0] = LoadTexture( "Textures/player.bmp" );
    texture[1] = LoadTexture( "Textures/playerTiltLeft.bmp" );
    texture[2] = LoadTexture( "Textures/playerTiltRight.bmp" );
    texture[3] = LoadTexture( "Textures/Bullet.bmp" );
    player.setup(texture);
    
    texture[0] = LoadTexture( "Textures/Enemy.bmp" );    
    texture[1] = LoadTexture( "Textures/Bullet.bmp" );
    enemy.setup(texture[0], texture[1]);*/
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

void Game::draw() {
    if(enemy.getVisible())
        enemy.draw();
    player.draw();
    collisions();
}

/*GLuint Game::LoadTexture( const char * filename )
{
  GLuint textures;
 
  int width, height;

  unsigned char * data;

  FILE * file;

  file = fopen( filename, "rb" );
  
  if ( file == NULL ) return 0;
  // printf("file opened\n");
  width = 2048;
  height = 2048;
  data = (unsigned char *)malloc( width * height * 4 );
  //int size = fseek(file,);
  fread( data, width * height * 4, 1, file );
  fclose( file );
 
  unsigned char t, t1, t2, t3;
  for(int j = 0; j < height; ++j){
      for(int i = 0; i < width; ++i) {
          //A, B, G, R
          t=data[i]; //A
          t1=data[i+1];//B
          t2=data[i+2];//G
          t3=data[i+3];//R
          //R, G, B, A
          data[j]=t2;
          data[j+1]=t1;
          data[j+2]=t;
          data[j+3]=t3;

          i+=4;
          j+=4;
      }
   }
   glGenTextures(1, &textures);
   glBindTexture(GL_TEXTURE_2D, textures);
  
   glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
   free( data );
   return textures;
}*/
