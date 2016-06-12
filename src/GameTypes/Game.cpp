#include "../../include/GameTypes/Game.h"

Game::Game() {
  //glutSetCursor(GLUT_CURSOR_NONE);
  seed = time(NULL);
  srand (seed);
}

void Game::draw() {  
  drawBackground();
  
  ship.draw();
  for(unsigned int i = 0; i < enemy.size(); ++i) {
      enemy[i]->draw();
  }
  //Collisions::drawQuadTree(); 
  //Collisions::drawHitBoxes(&ship, enemy);

  drawCrosshair();
  lbWave.draw();
}

void Game::setup() {
  srand(seed);
  
  wave = 0;
  
  lbWave.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.5, true);
  lbWave.setColour( 1.0,  0.0,  1.0);

  level = 1;
  isNew = true;
  ended = false;
  ChRadius = 20;
  type = MAINMENU;
  ChTexture = txt::LoadTexture("Textures/Game/Crosshair.png");
}

void Game::clean() {
  ship.clean();
  enemy.erase(enemy.begin(), enemy.end());
}

void Game::newWave() {
  //lbWave.setText((char*)"Wave 1", 6);
  wave++;
  std::stringstream ss;
  ss << wave;
  std::string str = "Wave " + ss.str();
  lbWave.setText(str.c_str(), str.length() + 1);
  lbWave.setTimer(40);
  
  unsigned int numOfEnemies = rand()%(10*wave);
  for(unsigned int i = 0; i < numOfEnemies; ++i) {
    switch(rand()%2 +1) {
      case 1:
        enemy.push_back(new BasicEnemy);       
        break;
      case 2:
        enemy.push_back(new CorruptedStarShip);
        break;
    }    
    enemy[i]->setup();
    enemy[i]->setX(rand()%(int)(SPACE_X_RESOLUTION-enemy[i]->getWidth()) + enemy[i]->getWidth()/2);
    enemy[i]->setY(rand()%(int)(SPACE_Y_RESOLUTION*(2+wave)) + (enemy[i]->getHeight()+SPACE_Y_RESOLUTION));
  }
  srand (rand()%RAND_MAX);
}

void Game::restart() {
  ship.setup();
}

void Game::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  if(isNew) {
    ship.setup();
    isNew = false;
  }
  
  if(enemy.size() == 0) 
    newWave();
  
  if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
    prevKeyState[ESC] = keyState[ESC];
    type = MAINMENU;
    ended = true;
  }
  
  ChX = mouseX;
  ChY = mouseY;
  ship.update(mouseX, mouseY, mouseBtnState, keyState, prevKeyState);
  
  for(unsigned int i = 0; i < enemy.size(); ++i) {
    enemy[i]->update();
    if(!enemy[i]->isVisible() && enemy[i]->getTotalNumOfBullets() == 0) {
        enemy.erase(enemy.begin()+i);
    } 
  }
  
  Collisions::detect(&ship, enemy);
  
  if(!ship.getVisible()) {
    type = MAINMENU;
    ended = true;    
  }
  
  lbWave.update();
}

void Game::drawCrosshair() { 
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, ChTexture);
  // Nice blue #1e00d5
  glColor3f(0.117647059f, 0, 0.835294197f);
  
  if(ship.getDistanceFromCursor() > MINIMUM_DISTANCETOSHIP) {
    lastChX = ChX;
    lastChY = ChY;
  } else {
    lastChX = ship.getX() +  MINIMUM_DISTANCETOSHIP*ship.getDirectionX();
    lastChY = ship.getY() + MINIMUM_DISTANCETOSHIP*ship.getDirectionY();
   
  }
  
  glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(lastChX-ChRadius, lastChY+ChRadius, 0.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(lastChX+ChRadius, lastChY+ChRadius, 0.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(lastChX+ChRadius, lastChY-ChRadius, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(lastChX-ChRadius, lastChY-ChRadius, 0.0);
  glEnd();  
  
  glColor3f(0.0, 0.0, 0.0f);
  glDisable(GL_TEXTURE_2D);
}

void Game::drawBackground() {

}
