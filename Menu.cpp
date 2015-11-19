#include "Menu.h"

#define TEXTURE_LOAD_ERROR 0

Menu::Menu() {
    height = 8;
    width = 8;  
    select = 0;
    numOptions = 2;
    screen = 0;
    printf("Menu Constructed\n");
}

void Menu::drawChar(int PosX, int PosY, float R, float G, float B, char str[25], int length) {
    glColor3f(R, G, B); // Text Colour
    glRasterPos2i(PosX, PosY); //coordinates of text
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f); //colour blue
    void * font = GLUT_BITMAP_HELVETICA_18;//set font http://www.opengl.org/documentation/specs/glut/spec3/node76.html#SECTION000111000000000000000
       
     for(int i = 0; i < length; i++) {
             
             glutBitmapCharacter(font, str[i]);
     }  
     glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    
}

void Menu::saveSettings() {
    std::ofstream data ("settings.in", std::ios_base::out);
    data<<showHitBox;
    data<<"\n";
    data<<collisionOn;
    data.close();
}

void Menu::readSettings() {
    std::ifstream data ("settings.in", std::ios_base::in);
    data>>showHitBox;
    data>>collisionOn;
    data.close();
}

void Menu::changeMenu(int newScreen) {
    screen = newScreen;
}

void Menu::setup() {
   
    textures[0] = LoadTexture( "Textures/Menu/Start.png" );
    textures[1] = LoadTexture( "Textures/Menu/Options.png" );
    textures[2] = LoadTexture( "Textures/Menu/Exit.png" );
    textures[3] = LoadTexture( "Textures/Menu/Selector.png" );
    textures[4] = LoadTexture( "Textures/Menu/Background.png" );
    
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
         if(select < numOptions)
             select++;
        }
    }
    
    if( (keyState[(unsigned char)'a'] == BUTTON_DOWN && prevKeyState[(unsigned char)'a'] != BUTTON_DOWN) || (keyState[(unsigned char)'d'] == BUTTON_DOWN && prevKeyState[(unsigned char)'d'] != BUTTON_DOWN) ) {
        switch(screen) {
            case 1:
                switch(select) {
                    case 0: //hit box on/off
                        if(showHitBox) {
                            showHitBox = 0;
                        } else {
                            showHitBox = 1;
                        }
                        break;
                    case 1://collision on/off
                        if(collisionOn) {
                            collisionOn = 0;
                        } else {
                            collisionOn = 1;
                        }
                        break;
                    case 2://return to main menu button
                        break;
                }
            break;
        }
    }
    
    if(keyState[13] == BUTTON_DOWN && prevKeyState[13] != BUTTON_DOWN) {
        switch(screen) {
           case 0:
               switch(select) {
                   case 0://game start
                       return 1;
                       break;
                   case 1://options
                      // prevKeyState[13] = keyState[13];
                       return 2;
                       break;
                   case 2://exit
                       return -1;
                       break;
               }
               break;
           case 1:
               switch(select) {
                   case 0://hit box on/off
                       break;
                   case 1://Controls
                       break;
                   case 2://Return to main menu
                       saveSettings();
                       return 3;
                       break;
               }
               break;
       }
    }
    
    prevKeyState[(unsigned char)'w'] = keyState[(unsigned char)'w'];
    prevKeyState[(unsigned char)'a'] = keyState[(unsigned char)'a'];
    prevKeyState[(unsigned char)'s'] = keyState[(unsigned char)'s'];
    prevKeyState[(unsigned char)'d'] = keyState[(unsigned char)'d'];

    prevKeyState[13] = keyState[13];
    
    return 0;
}

void Menu::drawBackground() {
    glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(0, 100, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(100, 100, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(100, 0, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0, 0, 0.0);
    glEnd();
    glColor4f(0.0f, 0.0f, 0.0f, 0.4f);
    glDisable(GL_TEXTURE_2D);
    
     glBegin(GL_QUADS); 
        glVertex3f(30, 60, 0.0);
        glVertex3f(70, 60, 0.0);
        glVertex3f(70, 0, 0.0);
        glVertex3f(30, 0, 0.0);
    glEnd();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
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
    
    //Selector
    glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); 
        glVertex3f(0, 60 - select*5, 0.0);
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(70, 60 - select*5, 0.0);
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(70, 55 - select*5, 0.0);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(0, 55 - select*5, 0.0);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    
    switch(screen) {
        //Menu
        case 0:         
            drawRectangle(35 - width/2, 54, 0);//start
            drawRectangle(35 - width/2, 49, 1);//options
            drawRectangle(35 - width/2, 44, 2);//exit
            break;
        //Options
        case 1:
            glPushMatrix();
            if(showHitBox) {
                char str[26] = "Show hit boxes: < True  >";;
                drawChar(35 - width/2, 56, 1.0f, 1.0f, 1.0f, str, 25);
            } else {
                char str[26] = "Show hit boxes: < False >";
                drawChar(35 - width/2, 56, 1.0f, 1.0f, 1.0f, str, 25);
            }
            glPopMatrix();
            
            glPushMatrix();
            if(!collisionOn) {
                char str[25] = "Collisions On: < True  >";
                drawChar(35 - width/2, 51, 1.0f, 1.0f, 1.0f, str, 25);
            } else {
                char str[25] = "Collisions On: < False >";
                drawChar(35 - width/2, 51, 1.0f, 1.0f, 1.0f, str, 25);
            }
            glPopMatrix();
            
            char str[25] = "Return";
            drawChar(35 - width/2, 46, 1.0f, 1.0f, 1.0f, str, 6);

            break;
    }
    

}

GLuint Menu::LoadTexture( const char * filename ) {
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
    size_t a = fread(header, 1, 8, fp);
    a = a - a;
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
