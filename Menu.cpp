#include "Menu.h"

Menu::Menu() {
    height = 4;
    width = 8;  
    select = 0;
    printf("Menu Constructed\n");
}

void Menu::setup() {
    textures[0] = LoadTexture( "Textures/Menu/Start.bmp" );
    textures[1] = LoadTexture( "Textures/Menu/Options.bmp" );
    textures[2] = LoadTexture( "Textures/Menu/Exit.bmp" );
    textures[3] = LoadTexture( "Textures/Menu/SelectedStart.bmp" );
    textures[4] = LoadTexture( "Textures/Menu/SelectedOptions.bmp" );
    textures[5] = LoadTexture( "Textures/Menu/SelectedExit.bmp" );
    textures[6] = LoadTexture( "Textures/Menu/Selector.bmp" );
    textures[7] = LoadTexture( "Textures/Menu/Background.bmp" );
    
    printf("Menu setup\n");
}
  
int Menu::keyPress(unsigned char* keyState, unsigned char* prevKeyState) {
    if(keyState[(unsigned char)'w'] == BUTTON_DOWN) {
        if(prevKeyState[(unsigned char)'w'] != BUTTON_DOWN) {
         if(select > 0)
              select--;
        }
    }

    if(keyState[(unsigned char)'s'] == BUTTON_DOWN) {
        if(prevKeyState[(unsigned char)'s'] != BUTTON_DOWN) {
         if(select < 2)
             select++;
        }
    }
    
    prevKeyState[(unsigned char)'s'] = keyState[(unsigned char)'s'];
    prevKeyState[(unsigned char)'w'] = keyState[(unsigned char)'w'];
    
    if(keyState[13] == BUTTON_DOWN) {
        switch(select) {
            case 0:
                return 1;
                break;
            case 1:
                return 2;
                break;
            case 2:
                return -1;
                break;
        }
    }
    
    return 0;
}

void Menu::drawBackground() {
    glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	
    glBegin(GL_QUADS);
        glTexCoord2f(0.05f, 1.0f); 
        glVertex3f(0, 100, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(100, 100, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(100, 0, 0.0);
        glTexCoord2f(0.05f, 0.0f);
        glVertex3f(0, 0, 0.0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void Menu::drawRectangle(float x, float y, int textnum) {

   glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, textures[textnum]);
	
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(x, y + height, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x + width, y + height, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x + width, y, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(x, y, 0.0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void Menu::draw() {
    drawBackground();
    switch(select) {
        case 0:
            drawRectangle(50 - width/2, 60 - height/2, 3);
            drawRectangle(50 - width/2, 50 - height/2, 1);
            drawRectangle(50 - width/2, 40 - height/2, 2);
            break;
        case 1:
            drawRectangle(50 - width/2, 60 - height/2, 0);
            drawRectangle(50 - width/2, 50 - height/2, 4);
            drawRectangle(50 - width/2, 40 - height/2, 2);
            break;
        case 2:
            drawRectangle(50 - width/2, 60 - height/2, 0);
            drawRectangle(50 - width/2, 50 - height/2, 1);
            drawRectangle(50 - width/2, 40 - height/2, 5);
            break;
    }        
  /*  glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	
    glBegin(GL_QUADS);
        glTexCoord2f(0.1f, 1.0f); 
        glVertex3f(0, 55, 0.0);
        glTexCoord2f(1.03f, 1.0f);
        glVertex3f(45, 55, 0.0);
        glTexCoord2f(1.03f, 0.0f);
        glVertex3f(45, 50, 0.0);
        glTexCoord2f(0.1f, 0.0f);
        glVertex3f(0, 50, 0.0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);*/
    
}

GLuint Menu::LoadTexture( const char * filename ) {
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
