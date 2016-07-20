#ifndef PROFILE_H
#define PROFILE_H

#include <fstream>
#include <string>

#include "./File.h"

class Profile {
  public:
    Profile();
    ~Profile();
    
    void Load(char* filename);
    void Save();   
    
    void addCoins(int coins) { this->coins += coins; }
    
    void setCoins(int coins) { this->coins = coins; }
    void setSelectedShip(int selectedShip) { this->selectedShip = selectedShip; }
    void setShipsUnlocked(int index, bool unlocked) { this->shipsUnlocked[index] = unlocked; }
    void setShipsBought(int index, bool bought) { this->shipsBought[index] = bought; }
    
    int getCoins() { return coins; }
    int getSelectedShip() { return selectedShip; }
    
    char* getUsername() { return filename; }
    
    float getVersion() { return version; }
    
    bool getShipsBought(int index) { return shipsBought[index]; }
    bool getShipsUnlocked(int index) { return shipsUnlocked[index]; }
    
  protected:
    void createNewProfile();
    char* filename;
    std::string str;
    
    int coins;
    int selectedShip;
    
    float version;

    bool shipsUnlocked[6];   
    bool shipsBought[6];    
    
    std::ifstream ifs;
    std::ofstream ofs;
};

#endif

