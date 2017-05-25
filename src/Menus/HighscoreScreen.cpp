#include "../../include/Menus/HighscoreScreen.h"

void HighscoreScreen::setStats(int coinsCollected, int numOfEnemiesKilled, int numOfPowerups) {
  std::stringstream ss;
  ss << coinsCollected;
  std::string str = "Coins Collected: " + ss.str();
  lb[23]->setText(str.c_str(), str.length());
  lb[23]->setVisible(true);
  
  std::stringstream ss1;
  ss1 << numOfEnemiesKilled;
  str = "Enemies Killed: " + ss1.str();
  lb[24]->setText(str.c_str(), str.length());
  lb[24]->setVisible(true);
  
  std::stringstream ss2;
  ss2 << numOfPowerups;
  str = "Powerups Collected: " + ss2.str();
  lb[25]->setText(str.c_str(), str.length());
  lb[25]->setVisible(true);
  
}

void HighscoreScreen::setup() {
  setup("");
  buttons[0]->setVisible(false);
  buttons[0]->disable();
  showingHighscores = true;
  buttons[2]->setY(SPACE_Y_RESOLUTION-200);
  buttons[2]->disable();
  for(int i = 0; i < 20; ++i)
    lb[i]->setVisible(true);
}

void HighscoreScreen::setup(std::string username) {
  Highscore *highscore = Highscore::instance(); 
  showingHighscores = false;
  this->username = username;
  
  Settings *settings = Settings::instance();
  float widthT = settings->getCurrentWindowWidth();
  float heightT = settings->getCurrentWindowHeight();
  float ratioX = widthT/(float)SPACE_X_RESOLUTION;
  float ratioY = heightT/(float)SPACE_Y_RESOLUTION;
  // Retry
  buttons.push_back(new Button);
  buttons[0]->setup(SPACE_X_RESOLUTION/4*3, SPACE_Y_RESOLUTION/10, 1.5f, (char*)"Retry");
  // Quit
  buttons.push_back(new Button);
  buttons[1]->setup(SPACE_X_RESOLUTION/4 +width/2, SPACE_Y_RESOLUTION/10, 1.5f,  (char*)"Quit");
  
  // Highscore screen
  buttons.push_back(new Button);
  buttons[2]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/10, 2.0f,  (char*)"Highscore");
  
  for(int i = 0; i < 20; i+=2) {
    names[i/2] = highscore->getName(i/2);
    highscores[i/2] = highscore->getScore(i/2);
    
    // Name
    std::stringstream ss;
    ss << i/2+1;
    std::string tempname = ss.str() + ". " + names[i/2]; 
    lb.push_back(new Label);
    lb[i]->setup(SPACE_X_RESOLUTION/4+BUTTONWIDTH, SPACE_Y_RESOLUTION/10 * ((7-(i/2*0.5)) + 0.5) - height/2, 30*ratioX, 30*ratioY);
    lb[i]->setText(tempname.c_str(), tempname.length());
    lb[i]->setColour(0.0, 1.0, 0.0);
    lb[i]->setVisible(false);
    // Score  
    std::stringstream ss1;
    ss1 << highscores[i/2];
    std::string tempscore = ss1.str(); 
    lb.push_back(new Label);
    lb[i+1]->setup(SPACE_X_RESOLUTION/4*3 - BUTTONWIDTH, SPACE_Y_RESOLUTION/10 * ((7-(i/2*0.5)) + 0.5) - height/2, 30*ratioX, 30*ratioY);
    lb[i+1]->setText(tempscore.c_str(), tempscore.length());
    lb[i+1]->setColour(0.0, 1.0, 0.0);
    lb[i+1]->setVisible(false);
  }
  // New High score
  lb.push_back(new Label);
  lb[20]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/5*4, 40*ratioX, 40*ratioY);
  lb[20]->setText((char*)"New Highscore!!!", 16);
  lb[20]->setColour(0.0, 1.0, 0.0);
  lb[20]->setVisible(false);
  
  // Score
  lb.push_back(new Label);
  lb[21]->setup(SPACE_X_RESOLUTION/2-BUTTONWIDTH/4, SPACE_Y_RESOLUTION/5*4 - BUTTONHEIGHT, 40*ratioX, 40*ratioY);
  lb[21]->setColour(0.0, 1.0, 0.0);
  
  // stats
  lb.push_back(new Label);
  lb[22]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/5*3, BUTTONWIDTH, BUTTONHEIGHT, (char*)"Textures/Menu/GameMenus/Stats.png");
  lb[22]->setVisible(false);
  
  // CoinsCollected
  //Num enemies killed 
  for(int i = 0; i < 3; ++i) {
    lb.push_back(new Label);
    lb[23+i]->setup(SPACE_X_RESOLUTION/2, SPACE_Y_RESOLUTION/5*3-BUTTONHEIGHT*(1+i), 30*ratioX, 30*ratioY);
    lb[23+i]->setColour(0.0, 1.0, 0.0);
    lb[23+i]->setVisible(false);
  }
} 

void HighscoreScreen::update(float mouseX, float mouseY, float deltaTime, unsigned int* mouseBtnState, unsigned int* prevMouseBtnState, unsigned char* keyState, unsigned char* prevKeyState) {
  ended = false;
  for(unsigned int i = 0; i < buttons.size(); ++i)
    buttons[i]->update(mouseX, mouseY, mouseBtnState, prevMouseBtnState);
  // Retru button
  if(buttons[0]->Clicked()) {
    type = ENDLESSGAME;
    ended = true;
  }
  // Quit button
  if(buttons[1]->Clicked()) {
    type = MAINMENU;
    ended = true;
  }
  // Highscore button
  if(buttons[2]->Clicked()) {
    if(showingHighscores) {    
      for(int i = 0; i < 20; ++i)
        lb[i]->setVisible(false);
      for(int i = 0; i < 5; ++i)
        lb[21+i]->setVisible(true);      
      buttons[2]->setText((char*)"Highscore");
      showingHighscores = false;
    } else {    
      for(int i = 0; i < 20; ++i)
        lb[i]->setVisible(true);
      for(int i = 0; i < 5; ++i)
        lb[21+i]->setVisible(false);        
      buttons[2]->setText((char*)"Stats");
      showingHighscores = true;
    }
  } 
}

void HighscoreScreen::setScore(int score) {
  Highscore *highscore = Highscore::instance(); 
   
  if(highscore->setNewHighscore(username, score)) {
    int i = highscore->getNewHighscorePos();
    for(int j = 9; j > i; j--) {
      names[j] = names[j-1];
      highscores[j] = highscores[j-1];
      std::stringstream ss;
      ss << j+1;
      std::string str = ss.str() + ". " + names[j].c_str(); 
      lb[j*2]->setText(str.c_str(), str.length());
      std::stringstream ss1;
      ss1 << highscores[j];
      std::string str1 = ss1.str();
      lb[j*2+1]->setText(str1.c_str(), str1.length());      
    }
    names[i] = highscore->getHighscoreName();
    std::stringstream ss;
    ss << i+1;
    std::string str = ss.str() + ". " + names[i].c_str(); 
    lb[i*2]->setText(str.c_str(), str.length());
    std::stringstream ss1;
    ss1 << highscore->getNewHighscore();
    std::string str1 = ss1.str();
    lb[i*2+1]->setText(str1.c_str(), str1.length());
    
    lb[20]->setVisible(true);
  }
  std::stringstream ss;
  ss << score;
  std::string strScore = "Your score: " + ss.str();
  lb[21]->setText(strScore.c_str(), strScore.length());
  lb[21]->setVisible(true);
  lb[22]->setVisible(true);

 // LoadHighscores(score);
}

void HighscoreScreen::restart() {}
