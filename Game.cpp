#include "Game.h"

#define TEXTURE_LOAD_ERROR 0

Game::Game() {
    srand (time(NULL));
    crntTime = clock();
    printf("Game Constructed\n");
}

void Game::setup(float aspectRatio) {

    std::ifstream data ("settings.in", std::ios_base::in);
    data>>showHitBox;
    data.close();
    
    increment = 0;
    printf("%d", showHitBox);
    glutSetCursor(GLUT_CURSOR_CROSSHAIR);
    level.setup();
    score = 0;
    GLuint playerTextures[5];
    playerTextures[0] = LoadTexture( "Textures/Game/Ship.png" );
    playerTextures[1] = LoadTexture( "Textures/Game/ShipLeft.png" );
    playerTextures[2] = LoadTexture( "Textures/Game/ShipRight.png" );
    playerTextures[3] = LoadTexture( "Textures/Game/PlayerBullet.png" );    
    player.setup(playerTextures, aspectRatio);
    
    GLuint enemyTexture[2];
    enemyTexture[0] = LoadTexture( "Textures/Game/Enemy.png" ); 
    enemyTexture[1] = LoadTexture( "Textures/Game/EnemyBullet.png" ); 
    //default
    for(int i = 0; i < 10; ++i) {
        enemy[i].setup(enemyTexture, aspectRatio);
        enemy[i].setX(i*10);
    }
    printf("Enemies Constructed\n");
    
    //Score
    texture[0] = LoadTexture( "Textures/Score/Zero.png" );
    texture[1] = LoadTexture( "Textures/Score/One.png" );
    texture[2] = LoadTexture( "Textures/Score/Two.png" );
    texture[3] = LoadTexture( "Textures/Score/Three.png" );
    texture[4] = LoadTexture( "Textures/Score/Four.png" );
    texture[5] = LoadTexture( "Textures/Score/Five.png" );
    texture[6] = LoadTexture( "Textures/Score/Six.png" );
    texture[7] = LoadTexture( "Textures/Score/Seven.png" );
    texture[8] = LoadTexture( "Textures/Score/Eight.png" );
    texture[9] = LoadTexture( "Textures/Score/Nine.png" );
    
    //Top Bar
    texture[10] = LoadTexture( "Textures/Hud/TopBar.png" );

    //Health Bar
    texture[11] = LoadTexture( "Textures/Hud/HealthBar.png" );
    level.Level1(enemy);
    
    //GameOver texture
    gameOverTexture = LoadTexture( "Textures/Hud/GameOver.png" );
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
            
        if(keyState[(unsigned char)'e'] == BUTTON_DOWN)
            player.rotateLeft();
        if(keyState[(unsigned char)'q'] == BUTTON_DOWN)
            player.rotateRight();
            
        //Fire player weapon
        if(keyState[32] == BUTTON_DOWN) { //Space Bar
            if(prevKeyState[32] != BUTTON_DOWN) {
               // printf("Space Bar pressed\n");
               if(increment > 5) {
                   increment = 0;
                   player.fire();
               }
             /*  if( (crntTime - shootTime) > 2000) {
                   shootTime = crntTime;
                   player.fire();
               }*/
            } else {
                //printf("%li\n", crntTime - shootTime);
               if(increment > 5) {
                   increment = 0;
                   player.fire();
               }                
/*if( (crntTime - shootTime) > 2000) {
                    shootTime = crntTime;
                    player.fire();
                }*/
            }
        }
        prevKeyState[32] = keyState[32];
            
        if(keyState[(unsigned char)'a'] == BUTTON_UP && keyState[(unsigned char)'d'] == BUTTON_UP) {
            player.stationaryImage();
        }
    }
}

void Game::drawHitBox(float Ax, float Ay, float Aw, float Ah) {
    glColor4f(1.0, 0.0f, 0.0f, 0.5);
    glBegin(GL_QUADS);
     
      //Bottom
      glVertex3f(Ax, Ay+0.1, 0.0);
      glVertex3f(Ax + Aw, Ay + 0.1, 0.0); 
      glVertex3f(Ax + Aw, Ay, 0.0);
      glVertex3f(Ax, Ay, 0.0);
      
      //Top
      glVertex3f(Ax, Ay+Ah, 0.0);
      glVertex3f(Ax + Aw, Ay + Ah, 0.0); 
      glVertex3f(Ax + Aw, Ay + Ah - 0.1, 0.0);
      glVertex3f(Ax, Ay + Ah - 0.1, 0.0);
      
      //Left
      glVertex3f(Ax, Ay+Ah, 0.0);
      glVertex3f(Ax + 0.1, Ay + Ah, 0.0); 
      glVertex3f(Ax + 0.1, Ay, 0.0);
      glVertex3f(Ax, Ay, 0.0);
      
      //Right
      glVertex3f(Ax + Aw - 0.1, Ay+Ah, 0.0);
      glVertex3f(Ax + Aw, Ay + Ah, 0.0); 
      glVertex3f(Ax + Aw, Ay, 0.0);
      glVertex3f(Ax + Aw - 0.1, Ay, 0.0);
              
    glEnd();
}

void Game::collisions() {   
    for(int i = 0; i < 10; ++i) {
        //float enemyRadius = pow((pow(enemy[i].getWidth()/2, 2) + pow(enemy[i].getHeight()/2, 2)), 0.5);
       // float playerRadius = pow((pow(player.getWidth()/2, 2) + pow(player.getHeight()/2, 2)), 0.5);
        //float totalRadius;
            
       // float diffx;
        //float diffy;
       // float distance;  
       
       //Player
       float Ax = player.getX()+0.5;
       float Ay = player.getY()-0.75;
       float Aw = player.getWidth()-1;
       float Ah = player.getHeight()-0.8;
            
       //Enemy     
       float Bx = enemy[i].getX() + ( (enemy[i].getWidth()/10.0f) * 2);
       float By = enemy[i].getY() + ( (enemy[i].getHeight()/10.0f) );
       float Bw = enemy[i].getWidth()-( (enemy[i].getWidth()/10.0f) * 3);
       float Bh = enemy[i].getHeight() - ( (enemy[i].getHeight()/10.0f) );
            
       //Player bullets     
       float Cx;
       float Cy;
       float Cw;
       float Ch;
       
       //Ememy Bullets
       float Dx = enemy[i].getBulletX();
       float Dy = enemy[i].getBulletY();
       float Dw = enemy[i].getBulletWidth();
       float Dh = enemy[i].getBulletHeight();
       if(showHitBox) {
           drawHitBox(Ax, Ay, Aw, Ah);
           drawHitBox(Bx, By, Bw, Bh);            
       }
        if(enemy[i].getVisible() && player.getVisible() && !player.getInvincible()) {            
            if( (Ax + Aw) >= Bx && Ax <= (Bx + Bw) && (Ay + Ah) >= By && Ay <= (By + Bh) ) {
                enemy[i].looseHealth(2);
                player.takeHealth(2);
                player.setVisible(false);
                playerTime = clock();
            }         
        }
          
        if(enemy[i].getVisible()) {  
            for(int j = 0; j < 10; ++j) {
                if(player.getBulletVisible(j)) {
                    Cx = player.getBulletX(j) + 0.2;
                    Cy = player.getBulletY(j) - 1;
                    Cw = player.getBulletWidth(j);
                    Ch = player.getBulletHeight(j);
                    if(showHitBox) {
                        drawHitBox(Cx, Cy, Cw, Ch);
                    }
                    if( (Cx + Cw) >= Bx && Cx <= (Bx + Bw) && (Cy + Ch) >= By && Cy <= (By + Bh) ) {
                         player.setBulletVisible(false, j);
                         score += enemy[i].looseHealth(1);
                    }        
                }
            }
        }
        
        if(player.getVisible() && !player.getInvincible() && enemy[i].getBulletVisible()) {   
            if(showHitBox) {
                drawHitBox(Dx, Dy, Dw, Dh);
            }
            if( (Ax + Aw) >= Dx && Ax <= (Dx + Dw) && (Ay + Ah) >= Dy && Ay <= (Dy + Dh) ) {
                enemy[i].setBulletVisible(false);
                player.takeHealth(1);
                player.setVisible(false);
                playerTime = clock();
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

void Game::drawGameOver() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gameOverTexture);
	
	//Top Bar    
	glBegin(GL_QUADS);
      glTexCoord2f(0.01f, 1.0f); 
      glVertex3f(35, 70, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(65, 70, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(65, 30, 0.0);
      glTexCoord2f(0.01f, 0.0f);
      glVertex3f(35, 30, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
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
	
    
    //Health Bar     
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
      glVertex3f(79, 97, 0.0);
      glVertex3f(79 + 20, 97, 0.0);
      glVertex3f(79 + 20, 95, 0.0);
      glVertex3f(79, 95, 0.0);
      
    glColor3f(1.0f, 0.0f, 0.0f);
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

bool Game::Tick(unsigned char* keyState, unsigned char* prevKeyState, float mouseX, float mouseY) {
    level.Tick(enemy);
    keyPress(keyState, prevKeyState);
    player.Tick(mouseX, mouseY);
    collisions();
    
    for(int i = 0; i < 10; ++i) {
        if(player.isAlive() && enemy[i].getVisible())
            enemy[i].Tick(player.getX()+player.getWidth()/2, player.getY()+player.getHeight()/2, player.getVisible());
    }
    
    if(player.isAlive() && !player.getVisible()) {
        if( (crntTime - playerTime) > 3000) {
            shootTime = playerTime;
            player.respawn(50, 5);
        }
    }  
    
    if(player.getHealth() <= 0)  
        return false;
    increment++;
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
    int width;
    int height;
    
    //header for testing if it is a png
    png_byte header[8];
 
    //open file as binary
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
      return TEXTURE_LOAD_ERROR;
    }
 
    //read the header
    fread(header, 1, 8, fp);
 
    //test if png
    int is_png = !png_sig_cmp(header, 0, 8);
    if (!is_png) {
      fclose(fp);
      return TEXTURE_LOAD_ERROR;
    }
 
    //create png struct
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
      fclose(fp);
      return (TEXTURE_LOAD_ERROR);
    }
 
    //create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
      png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
      fclose(fp);
      return (TEXTURE_LOAD_ERROR);
    }
 
    //create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
      png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
      fclose(fp);
      return (TEXTURE_LOAD_ERROR);
    }
 
    //png error stuff, not sure libpng man suggests this.
    if (setjmp(png_jmpbuf(png_ptr))) {
      png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
      fclose(fp);
      return (TEXTURE_LOAD_ERROR);
    }
 
    //init png reading
    png_init_io(png_ptr, fp);
 
    //let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);
 
    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);
  
    //variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 twidth, theight;
 
    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type, NULL, NULL, NULL);
 
    //update width and height based on png info 
    width = twidth;
    height = theight;
 
    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);
 
    // Row size in bytes.
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
 
    // Allocate the image_data as a big block, to be given to opengl
    png_byte *image_data = new png_byte[rowbytes * height];
    if (!image_data) {
      //clean up memory and close stuff
      png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
      fclose(fp);
      return TEXTURE_LOAD_ERROR;
   }
 
   //row_pointers is for pointing to image_data for reading the png with libpng
   png_bytep *row_pointers = new png_bytep[height];
   if (!row_pointers) {
     //clean up memory and close stuff
     png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
     delete[] image_data;
     fclose(fp);
     return TEXTURE_LOAD_ERROR;
   }
   // set the individual row_pointers to point at the correct offsets of image_data
   for (int i = 0; i < height; ++i)
     row_pointers[height - 1 - i] = image_data + i * rowbytes;
 
   //read the png into image_data through row_pointers
   png_read_image(png_ptr, row_pointers);
 
   //Now generate the OpenGL texture object
   GLuint texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, width, height, 0,
       GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*) image_data);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
 
   //clean up memory and close stuff
   png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
   delete[] image_data;
   delete[] row_pointers;
   fclose(fp);
 
   return texture;
}
