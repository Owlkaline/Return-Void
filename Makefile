#!/usr/bin/make -f
CC = g++
CFLAGS  = -Wall -g -O3
PROG = Return-void

SRCS = main.cpp Menu.cpp Game.cpp Level.cpp Player.cpp Enemy.cpp Bullet.cpp

LIBS = -lglut -lGLU -lGL -lpng

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG) 

