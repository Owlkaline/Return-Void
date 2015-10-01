#include "Bullet.h"

#include <stdlib.h>

Bullet::Bullet() {
        width = 3;
        height = 4;
        x = 0.0f;
        y = 0.0f;  
        boundryX = 100 - width;
        boundryY = 100 - height;
        isVisible = false;
        //setup();
        printf("Bullet Constructed\n");
   }
   
void Bullet::setup(GLuint newText) {
    texture = newText;
}

    
void Bullet::draw() {
    moveUp();   
    //glColor3f(0.0, 1.0, 0.0);
    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    if(x > boundryX)
        x = boundryX;
    if(y > boundryY) {
      //  y = boundryY;
        isVisible = false;
    }
    
    
    glEnable(GL_TEXTURE_2D);
    
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBegin(GL_POLYGON);
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

void Bullet::fire(float newX, float newY, float mSpeed) {
    x = newX - width/2;
    y = newY;
    speed = mSpeed;
    isVisible = true;
    //printf("new bullet fired\n");
  //  draw();
}

float Bullet::getX() { return x; }
float Bullet::getY() { return y; }
bool Bullet::getVisible() { return isVisible; }
void Bullet::moveUp() { y += speed; }
void Bullet::moveDown() { y -= speed; }

GLuint Bullet::LoadTexture( const char * filename )
{
  GLuint textures;
 
  int width, height;

  unsigned char * data;

  FILE * file;

  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
 // printf("file opened\n");
  width = 1024;
  height = 512;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

  for(int i = 0; i < width * height ; ++i) {
      int index = i*3;
      unsigned char B,R;
      B = data[index];
      R = data[index+2];

      data[index] = R;
      data[index+2] = B;
   }
   
   glGenTextures(1, &textures);
   glBindTexture(GL_TEXTURE_2D, textures);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
   free( data );
   printf("bullet Texture Loaded\n");
   return textures;
    /*glGenTextures( 1, &textures );
    glBindTexture( GL_TEXTURE_2D, textures );
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );


    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );    
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width,   height, 0, GL_RGB, GL_UNSIGNED_BYTE, data );
    //gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
    free( data );

    return textures;*/
}
