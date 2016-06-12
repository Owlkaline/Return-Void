#!/usr/bin/make -f
CC = g++
CFLAGS  = -Wall -g -O3
PROG = Return-void

SRCS = ./src/main.cpp ./src/GameTypes/Game.cpp ./src/GameTypes/MainMenu.cpp ./src/Namespaces/LoadTexture.cpp ./src/Namespaces/Collisions.cpp ./src/Menus/Button.cpp ./src/Ships/Ship.cpp ./src/Enemies/BasicEnemy.cpp ./src/Enemies/CorruptedStarShip.cpp ./src/Mounts/BasicMount.cpp ./src/Mounts/TriangleMount.cpp ./src/Weapons/RedPlasma.cpp ./src/Weapons/BluePlasma.cpp  ./src/Weapons/GreenPlasma.cpp 

LIBS = -lglut -lGLU -lGL -lpng

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG) 

