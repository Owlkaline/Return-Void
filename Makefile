#!/usr/bin/make -f
CC = g++
CFLAGS  = -Wall -g -O3
PROG = Return-void

SRCS = ./src/main.cpp ./src/Game.cpp ./src/MainMenu.cpp ./src/Ship.cpp ./src/LoadTexture.cpp ./src/Button.cpp ./src/BluePlasma.cpp ./src/BasicMount.cpp

LIBS = -lglut -lGLU -lGL -lpng

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG) 

