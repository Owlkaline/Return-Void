#include "Menu.h"

Menu::Menu() {
    height = 4;
    width = 8;  
    select = 0;
    printf("Menu Constructed\n");
}

void Menu::setup(GLuint *newtext) {
    textures[0] = newtext[6];
    textures[1] = newtext[7];
    textures[2] = newtext[8];
    textures[3] = newtext[9];
    textures[4] = newtext[10];
    textures[5] = newtext[11];
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

void Menu::drawRectangle(float x, float y, int textnum) {

   glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, textures[textnum]);
	glEnable(GL_BLEND);
	glColor4ub(255,255,255,255);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); 
        glVertex3f(x, y + height, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(x + width, y + height, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(x + width, y, 0.0);
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(x, y, 0.0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void Menu::draw() {
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
}
