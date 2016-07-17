#ifndef PROFILE_H
#define PROFILE_H

#include <fstream>

#include "./File.h"
#include "../defines.h"

class Profile {
  public:
    Profile();
    ~Profile();
    void Load();
    void Save();
    float getVersion() { return version; }
    int getCoins() { return coins; }
    int getSelectedShip() { return selectedShip; }
    bool getShipsUnlocked(int index) { return shipsUnlocked[index]; }
    bool getShipsBought(int index) { return shipsBought[index]; }
    
    void setCoins(int coins) { this->coins = coins; }
    void setSelectedShip(int selectedShip) { this->selectedShip = selectedShip; }
    void setShipsUnlocked(int index, bool unlocked) { this->shipsUnlocked[index] = unlocked; }
    void setShipsBought(int index, bool bought) { this->shipsBought[index] = bought; }
  protected:
    void createNewProfile();
    std::ifstream ifs;
    std::ofstream ofs;
    float version;
    int coins;
    int selectedShip;
    bool shipsUnlocked[6];   
    bool shipsBought[6];    
};

#endif

