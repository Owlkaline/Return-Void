#!/usr/bin/make -f
CC = g++
CFLAGS  = -Wall -g
PROG = Game

SRCS = main.cpp Game.cpp Player.cpp Enemy.cpp Bullet.cpp  

LIBS = -lglut -lGLU -lGL

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG) 

