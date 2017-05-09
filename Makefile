#!/usr/bin/make -f
CC = g++
CFLAGS  = -Wall -g -O3 -I/home/akuma/Git/Return-Void/include/stb
PROG = Return-void

SRCS = $(SRCMAIN) $(SRCMENU) $(SRCGAME) $(SRCSTORY) $(SRCENEMIES) $(SRCMOUNTS) $(SRCBULLETS) $(SRCDROPS)

SRCMAIN =./src/main.cpp ./src/Namespaces/LoadTexture.cpp ./src/Namespaces/Collisions.cpp ./src/Namespaces/Random.cpp ./src/Namespaces/File.cpp ./src/Namespaces/Movement.cpp ./src/Namespaces/Settings.cpp ./src/Namespaces/Profile.cpp ./src/Namespaces/Highscore.cpp ./src/Ships/GalacticShip.cpp ./src/Ships/FighterShip.cpp ./src/Ships/HeroShip3.cpp

SRCMENU =./src/Menus/SettingsMenu.cpp ./src/Menus/PausedMenu.cpp ./src/Menus/Button.cpp ./src/Menus/Label.cpp ./src/Menus/CheckBox.cpp ./src/Menus/HighscoreScreen.cpp ./src/Menus/Shop.cpp ./src/Menus/Shipbox.cpp ./src/Menus/FloatingText.cpp ./src/Menus/Text.cpp

SRCSTORY =./src/Story/StarMap.cpp

SRCGAME =./src/GameTypes/Game.cpp ./src/Menus/MainMenu.cpp ./src/Misc/Effects.cpp ./src/Misc/SmallExplosion.cpp ./src/GameTypes/Story.cpp

SRCENEMIES =./src/Enemies/BasicEnemy.cpp ./src/Enemies/CorruptedStarShip.cpp ./src/Enemies/HypnoEnemy.cpp ./src/Enemies/AlphaOne.cpp ./src/Enemies/DotEnemy.cpp

SRCMOUNTS =./src/Mounts/BasicMount.cpp ./src/Mounts/TriangleMount.cpp ./src/Mounts/HypnoMount.cpp ./src/Mounts/PurpleMount.cpp ./src/Mounts/AlphaOneMount.cpp ./src/Mounts/DotMount.cpp ./src/Mounts/MountType1.cpp ./src/Mounts/MountType2.cpp ./src/Mounts/MountType3.cpp

SRCBULLETS =./src/Weapons/RedPlasma.cpp ./src/Weapons/BluePlasma.cpp  ./src/Weapons/GreenPlasma.cpp ./src/Weapons/PurplePlasma.cpp ./src/Weapons/Spiral.cpp ./src/Weapons/AlphaOnePlasma.cpp ./src/Weapons/DotBullet.cpp

SRCDROPS =./src/Drops/Coins.cpp ./src/Drops/Health.cpp ./src/Drops/Shield.cpp

LIBS = -lglfw -lGLC -lGLU -lGL -lpng

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG) 

