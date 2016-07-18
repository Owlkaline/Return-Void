#include "../../include/GameTypes/Game.h"

Game::Game() {
  seed = time(NULL);
  boostRand.newSeed(seed);
}

void Game::draw() {
  drawBackground();  

  for(unsigned int i = 0; i < powerups.size(); ++i) 
    powerups[i]->draw();
 
  ship.draw();

  for(unsigned int i = 0; i < enemy.size(); ++i) {
    enemy[i]->draw();
  }

  ship.drawHealthBar();

  if(DRAWQUADTREE)
    Collisions::drawQuadTree();
  if(DRAWHITBOX)
    Collisions::drawHitBoxes(&ship, enemy, powerups);

  lbWave.draw();
  lbScore.draw();
  lbCoins.draw();
  if(paused)
    pMenu.draw();

  if(inHighscore) 
    highscore.draw();
    
  drawCrosshair();
}

void Game::setup() {
  printf("Game Setting up...");
  boostRand.newSeed(seed);

  profile.Load();
  settings.Load();

  paused = false;
  inHighscore = false;
  highscore.setup();

  score = 0;
  wave = 0;
  offsetY = 0;
  
  ship.setup(settings.getRelativeMovement());

  lbWave.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.5, true);
  lbWave.setColour( 1.0,  0.0,  1.0);

  lbScore.setup(SPACE_X_RESOLUTION-200, SPACE_Y_RESOLUTION/20 * 19.2, 0.3, false);
  lbScore.setColour( 1.0,  1.0,  1.0);
  
  lbCoins.setup(SPACE_X_RESOLUTION-100, 30, 0.3, false);
  lbCoins.setColour( 1.0,  1.0,  1.0);
  
  std::stringstream ss;
  ss << score;
  std::string strScore = "Score: " + ss.str();
  lbScore.setText(strScore.c_str(), strScore.length() + 1);
  
  lbCoins.setText("$", 1);
 
  level = 1;
  isNew = true;
  ended = false;
  ChRadius = 20;
  type = MAINMENU;
  ChTexture = txt::LoadTexture("Textures/Game/Crosshair.png");
  background = txt::LoadTexture("Textures/Game/Background.png");

  pMenu.setup();
  printf(" Game Setup\n");
}

void Game::clean() {
  printf("Game Cleaning...");
  pMenu.clean();
  highscore.clean();
  ship.clean();
  enemy.clear();
  powerups.clear();
  enemy.erase(enemy.begin(), enemy.end());
  powerups.erase(powerups.begin(), powerups.end()); 
  printf("Game Clean\n");
}

void Game::newWave() {
  printf("New Enemy Wave\n");
  wave++;
  
  std::stringstream ss;
  ss << wave;
  std::string str = "Wave " + ss.str();
  lbWave.setText(str.c_str(), str.length() + 1);
  lbWave.setTimer(40);
  
  if(wave%10 == 0) {
    enemy.push_back(new AlphaOne);
    enemy[0]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION*2, ALPHAONE, NOTHING);
  } else {
    unsigned int numOfEnemies = 0;
    while(numOfEnemies == 0)
      numOfEnemies = boostRand.Int(wave, wave*10);//wave*10;//boostRand.Int(0, wave*10);
    
    //  printf("Enemies: %d\n", numOfEnemies);
    for(unsigned int i = 0; i < numOfEnemies; ++i) {
      int type = -1;
   
      switch(boostRand.Int(0.35, 0.35, 0.3)) {
        case 1:
          printf("Basic Enemy Spawned\n");
          enemy.push_back(new BasicEnemy); 
          type = FALL;
          break;
        case 2:
          printf("Corrupted Enemy Spawned\n");
          enemy.push_back(new CorruptedStarShip);
          type = SINWAVE;
          break;
        case 3: 
          printf("Hypno Enemy Spawned\n");
          enemy.push_back(new HypnoEnemy);
          type = SEMICIRCLE;
          break;
      }
      enemy[i]->defaults();
      int powerup = boostRand.Int(0.5, 0.3, 0.1, 0.1) - 1;
      float x = boostRand.Int((int)(enemy[i]->getWidth()/2), SPACE_X_RESOLUTION-enemy[i]->getWidth());
      float y = boostRand.Int((enemy[i]->getHeight()+SPACE_Y_RESOLUTION), (int)(SPACE_Y_RESOLUTION*(2+wave)));
      enemy[i]->setup(x, y, type, powerup);
    }
  }
  

  
  printf("New Seed\n"); 
  boostRand.newSeed(boostRand.Int(0, 9999999999));
}

void Game::restart() {
  printf("Game Restarting...\n");
  profile.Save();
  clean();
  setup();  
}

void Game::update(float mouseX, float mouseY, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  ChX = mouseX;
  ChY = mouseY;

  if(!inHighscore) {
    if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
      prevKeyState[ESC] = keyState[ESC];
      paused = !paused;
      printf("Game pause: %d\n", paused);
    }
    
    if(!paused) {      
      if(enemy.size() == 0)
        newWave();
           
      offsetY-=2;
      if(offsetY <= -1080)
        offsetY=0;
        
      ship.update(mouseX, mouseY, mouseBtnState, keyState, prevKeyState);
    //  printf("\n%d: ", enemy.size());
      for(unsigned int i = 0; i < enemy.size(); ++i) {

   // printf("E: %d, X: %f, Y: %f, Width: %f, Height: %f\n", i, enemy[i]->getMountX(0), enemy[i]->getMountY(0), enemy[i]->getMountWidth(0), enemy[i]->getMountHeight(0));

        enemy[i]->update(ship.getX(), ship.getY());
        if(enemy[i]->getWaskilled()) {
          score += enemy[i]->getScore();
          std::stringstream ss;
          ss << score;
          std::string str = "Score: " + ss.str();
          lbScore.setText(str.c_str(), str.length() + 1);
          ship.boost();
          
          bool nothing = false; 
          switch(enemy[i]->dropPowerup()) {
            case NOTHING:
              nothing = true;
              break;
            case COIN:
              powerups.push_back(new Coins);
              break;
            case HEALTH:
              powerups.push_back(new Health);
              break;
            case SHIELD:
              powerups.push_back(new Shield);
              break;
          }
          if(!nothing) {
            int j = powerups.size()-1;
            powerups[j]->setup(enemy[i]->getX(), enemy[i]->getY());
          }
        }
        if(!enemy[i]->isVisible() && enemy[i]->getTotalNumOfBullets() == 0) {
          enemy.erase(enemy.begin()+i);
        }        
      }
      for(unsigned int i = 0; i < powerups.size(); ++i) {
        powerups[i]->update();
        if(!powerups[i]->isVisible()) {
          powerups.erase(powerups.begin()+i);
        }
      }

      lbWave.update();

      Collisions::detect(&ship, enemy, powerups);

      if(!ship.getVisible()) {
        inHighscore = true;
        highscore.setScore(score);
        printf("Player died, HighscoreScreen\n");
        profile.addCoins(coins);
      }
    } else {
      pMenu.update(mouseX, mouseY, mouseBtnState, prevMouseBtnState, keyState, prevKeyState);
      if(!pMenu.isPaused())
        paused = !paused;
      if(pMenu.hasEnded()) {
        type = MAINMENU;
        ended = true;
        printf("Returning to Menu From pause screen\n");
      }
    }
    coins = ship.getCoins();
    std::stringstream ss;
    ss << coins;
    std::string str = "$" + ss.str();
    lbCoins.setText(str.c_str(), str.length());
  } else {
    if(keyState[ESC] == BUTTON_DOWN && prevKeyState[ESC] != BUTTON_DOWN) {
      prevKeyState[ESC] = keyState[ESC];
      type = MAINMENU;
      ended = true;
      printf("Returning to Menu, from highscore screen\n");
    }
    highscore.update( mouseX, mouseY, mouseBtnState, prevMouseBtnState, keyState, prevKeyState);
    if(highscore.hasEnded()) {
      switch(highscore.getEndType()) {
        case MAINMENU:
          type = MAINMENU;
          ended = true;
          profile.Save();
          printf("Return to Menu from Quit Button pressed on highscore screen\n");
          break;
        case GAME:
          restart();
          break;
      }
    }
  } 
}

void Game::drawCrosshair() {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, ChTexture);
  // Nice blue #1e00d5
  //lColor3f(0.117647059f, 0, 0.835294197f);
  glColor4f(1, 0.643137255, 0, 1.0f);
  if(!paused && !inHighscore) {
    if(ship.getDistanceFromCursor() > MINIMUM_DISTANCETOSHIP) {
      lastChX = ChX;
      lastChY = ChY;
    } else {
      lastChX = ship.getX() +  MINIMUM_DISTANCETOSHIP*ship.getDirectionX();
      lastChY = ship.getY() + MINIMUM_DISTANCETOSHIP*ship.getDirectionY();
    }
  } else {
    lastChX = ChX;
    lastChY = ChY;
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

  glColor3f(1.0, 1.0, 1.0f);
  glDisable(GL_TEXTURE_2D);

}

void Game::drawBackground() {
    // Background
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, background);
 
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(0, SPACE_Y_RESOLUTION*2+offsetY, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(SPACE_X_RESOLUTION, SPACE_Y_RESOLUTION*2+offsetY, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(SPACE_X_RESOLUTION, SPACE_Y_RESOLUTION+offsetY, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(0, SPACE_Y_RESOLUTION+offsetY, 0.0);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, background);
 
    glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f);
      glVertex3f(0, SPACE_Y_RESOLUTION+offsetY, 0.0);
      glTexCoord2f(1.0f, 1.0f);
      glVertex3f(SPACE_X_RESOLUTION, SPACE_Y_RESOLUTION+offsetY, 0.0);
      glTexCoord2f(1.0f, 0.0f);
      glVertex3f(SPACE_X_RESOLUTION, 0+offsetY, 0.0);
      glTexCoord2f(0.0f, 0.0f);
      glVertex3f(0, 0+offsetY, 0.0);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}
