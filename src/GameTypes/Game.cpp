#include "../../include/GameTypes/Game.h"

Game::Game() {
  seed = time(NULL);
  boostRand.newSeed(seed);
}

void Game::draw() {
  drawBackground();  

  for(unsigned int i = 0; i < powerups.size(); ++i) 
    powerups[i]->draw();
 
  ship[0]->draw();

  for(unsigned int i = 0; i < enemy.size(); ++i) 
    enemy[i]->draw();
  
  for(unsigned int i = 0; i < Ftext.size(); ++i)
    Ftext[i]->draw();
  
  ship[0]->drawHealthBar();

  if(DRAWQUADTREE)
    Collisions::drawQuadTree();
  if(DRAWHITBOX)
    Collisions::drawHitBoxes(ship, enemy, powerups);

  lbWave.draw();
  lbWaveStatic.draw();
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

  profile.Load((char*)"You   ");
  settings.Load();

  paused = false;
  inHighscore = false;
  highscore.setup(profile.getUsername());

  score = 0;
  wave = 0;
  offsetY = 0;
  numOfEnemiesKilled = 0;
  numOfPowerupsCollected = 0;
  
  selected = profile.getSelectedShip();
  
  switch(selected) {
    case 0:
      ship.push_back(new GalacticShip);
      break;
    case 1:
      ship.push_back(new FighterShip);
      break;
    default:
      printf("Error in Game.cpp: Unkown ship selected");
      exit(0);
      break;
  }
  
  ship[0]->setup(settings.getRelativeMovement());

  lbWave.setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/2, 0.5, true);
  lbWave.setColour( 1.0,  0.0,  1.0);
  
  lbWaveStatic.setup(80, SPACE_Y_RESOLUTION-80, 0.3, false);
  lbWaveStatic.setColour(1.0, 1.0, 1.0);

  lbScore.setup(SPACE_X_RESOLUTION-200, SPACE_Y_RESOLUTION/20 * 19.2, 0.3, false);
  lbScore.setColour( 1.0,  1.0,  1.0);
  
  lbCoins.setup(SPACE_X_RESOLUTION-150, 30, 0.3, false);
  lbCoins.setColour( 1.0,  1.0,  1.0);
  
  std::stringstream ss;
  ss << score;
  std::string strScore = "Score: " + ss.str();
  lbScore.setText(strScore.c_str(), strScore.length() + 1);
  
  lbCoins.setText("Coins: ", 7);
 
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
  ship.clear();
  
  enemy.clear();
  powerups.clear();
  Ftext.clear();
  
  ship.erase(ship.begin(), ship.end());
  enemy.erase(enemy.begin(), enemy.end());
  powerups.erase(powerups.begin(), powerups.end()); 
  Ftext.erase(Ftext.begin(), Ftext.end());
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
  
  lbWaveStatic.setText(str.c_str(), str.length() + 1);
  
  if(wave%10 == 0) {
    enemy.push_back(new AlphaOne);
    enemy[0]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION*2, ALPHAONE, NOTHING);
    enemy[0]->setHealth(enemy[0]->getHealth() * (wave/10));
    for(int i = 0; i < enemy[0]->getNumOfMounts(); ++i)
      enemy[0]->setMountHealth(i, enemy[0]->getMountHealth(i) * ((wave/10)*2));
  } else {
    unsigned int numOfEnemies = 0;
    while(numOfEnemies == 0) {
   //   if(wave < 10) {
        numOfEnemies = boostRand.Int(5, wave*5);
 //     } else {
    //    numOfEnemies = boostRand.Int(wave+wave, wave*wave+wave);
   //   }
    }
    for(unsigned int i = 0; i < numOfEnemies; ++i) {
      int type = -1;
   
     switch(boostRand.Int(0.4, 0.4, 0.05, 0.15)) {
    // switch(boostRand.Int(0.1, 0.1, 0.1, 0.7)) {
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
        case 4:
          printf("Dot enemy spawned\n");
          enemy.push_back(new DotEnemy);
          type = RIGHTSIDEFALL;
      }
      enemy[i]->defaults();
     // if()
      int powerup = boostRand.Int(0.5, 0.3, 0.1, 0.1) - 1;
      float x = boostRand.Int((int)(enemy[i]->getWidth()/2), SPACE_X_RESOLUTION-enemy[i]->getWidth());
      float y = 0;
      if(wave != 1 && (wave-1)%10 == 0) {
        y = boostRand.Int((enemy[i]->getHeight()+SPACE_Y_RESOLUTION*2), (int)(SPACE_Y_RESOLUTION*2+(wave*0.5*SPACE_Y_RESOLUTION)));
      } else {
        y = boostRand.Int((enemy[i]->getHeight()+SPACE_Y_RESOLUTION), (int)(SPACE_Y_RESOLUTION+(wave*0.5*SPACE_Y_RESOLUTION)));
      }
      
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
      printf("Game pause: %s\n", paused ? "True" : "False");
    }
    
    if(!paused) {      
      if(enemy.size() == 0)
        newWave();
        
      // Background sccrolling   
      offsetY-=2;
      if(offsetY <= -1080)
        offsetY=0;
        
      ship[0]->update(mouseX, mouseY, mouseBtnState, keyState, prevKeyState);
      
      // Updated enemy and checked if it was killed
      for(unsigned int i = 0; i < enemy.size(); ++i) {
        enemy[i]->update(ship[0]->getX(), ship[0]->getY());
        if(enemy[i]->getWaskilled()) {
          numOfEnemiesKilled++;
          score += enemy[i]->getScore();
          std::stringstream ss;
          ss << score;
          std::string str = "Score: " + ss.str();
          lbScore.setText(str.c_str(), str.length() + 1);          
          
          std::stringstream sf;
          sf << enemy[i]->getScore();;
          std::string str1 = "+" + sf.str();
          Ftext.push_back(new FloatingText);
          Ftext[Ftext.size()-1]->setup(enemy[i]->getX(), enemy[i]->getY(), str1.c_str(), str1.length(), 0.2);
          Ftext[Ftext.size()-1]->setColour(0.0, 1.0, 0.0);
          
          ship[0]->boost();
          
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
          if(enemy[i]->getIsBoss()) {
            for(int k = 0; k < 5; ++k) {
              powerups.push_back(new Coins);
              int j = powerups.size()-1;
              powerups[j]->setup(enemy[i]->getX()-100+k*50, enemy[i]->getY());
            }
            for(int k = 0; k < 3; ++k) {
              powerups.push_back(new Health);
              int j = powerups.size()-1;
              powerups[j]->setup(enemy[i]->getX()-50+k*50, enemy[i]->getY()-50);
            }
            for(int k = 0; k < 2; ++k) {
              powerups.push_back(new Shield);
              int j = powerups.size()-1;
              powerups[j]->setup(enemy[i]->getX()-50+k*50, enemy[i]->getY()-100);
            }
          }
        }
        if(!enemy[i]->isVisible() && enemy[i]->getTotalNumOfBullets() == 0) {
          enemy.erase(enemy.begin()+i);
        }        
      }
      for(unsigned int i = 0; i < powerups.size(); ++i) {
        powerups[i]->update();
        if(powerups[i]->getCollected()) {
          numOfPowerupsCollected++;
          std::string str = powerups[i]->getName();
          Ftext.push_back(new FloatingText);
          Ftext[Ftext.size()-1]->setup(powerups[i]->getX(), powerups[i]->getY(), str.c_str(), str.length(), 0.2);
          Ftext[Ftext.size()-1]->setColour(0.0, 1.0, 0.0);
          
          powerups.erase(powerups.begin()+i);
        } else if (!powerups[i]->getVisible()) {
          powerups.erase(powerups.begin()+i);
        }
        
      }
      for(unsigned int i = 0; i < Ftext.size(); ++i) {
        Ftext[i]->update();
        if(!Ftext[i]->getVisible()) {
          Ftext.erase(Ftext.begin()+i);
        }
      }
        
      lbWave.update();

      Collisions::detect(ship, enemy, powerups);

      if(!ship[0]->getVisible()) {
        inHighscore = true;
        highscore.setScore(score);
        highscore.setStats(coins, numOfEnemiesKilled, numOfPowerupsCollected);
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
    coins = ship[0]->getCoins();
    std::stringstream ss;
    ss << coins;
    std::string str = "Coins: " + ss.str();
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
    if(ship[0]->getDistanceFromCursor() > MINIMUM_DISTANCETOSHIP) {
      lastChX = ChX;
      lastChY = ChY;
    } else {
      lastChX = ship[0]->getX() +  MINIMUM_DISTANCETOSHIP*ship[0]->getDirectionX();
      lastChY = ship[0]->getY() + MINIMUM_DISTANCETOSHIP*ship[0]->getDirectionY();
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
