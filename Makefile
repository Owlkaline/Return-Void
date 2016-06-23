#!/usr/bin/make -f
CC = g++
CFLAGS  = -Wall -g -O3
PROG = Return-void

SRCS = $(SRCMAIN) $(SRCMENU) $(SRCGAME) $(SRCENEMIES) $(SRCMOUNTS) $(SRCBULLETS) $(SRCDROPS)

SRCMAIN =./src/main.cpp ./src/Namespaces/LoadTexture.cpp ./src/Namespaces/Collisions.cpp ./src/Namespaces/Random.cpp ./src/Namespaces/File.cpp ./src/Ships/Ship.cpp  

SRCMENU =./src/GameTypes/SettingsMenu.cpp ./src/Menus/PausedMenu.cpp ./src/Menus/Button.cpp ./src/Menus/Label.cpp ./src/Menus/CheckBox.cpp ./src/Menus/HighscoreScreen.cpp

SRCGAME =./src/GameTypes/Game.cpp ./src/GameTypes/MainMenu.cpp

SRCENEMIES =./src/Enemies/BasicEnemy.cpp ./src/Enemies/CorruptedStarShip.cpp ./src/Enemies/HypnoEnemy.cpp

SRCMOUNTS =./src/Mounts/BasicMount.cpp ./src/Mounts/TriangleMount.cpp ./src/Mounts/HypnoMount.cpp

SRCBULLETS =./src/Weapons/RedPlasma.cpp ./src/Weapons/BluePlasma.cpp  ./src/Weapons/GreenPlasma.cpp ./src/Weapons/Spiral.cpp

SRCDROPS =./src/Drops/Coins.cpp ./src/Drops/Health.cpp ./src/Drops/Shield.cpp

LIBS = -lglut -lGLU -lGL -lpng

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG) 

