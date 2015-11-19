#!/usr/bin/make -f
CC = g++
CFLAGS  = -Wall -g -O3
PROG = Return-void

SRCS = ./scr/main.cpp ./scr/Menu.cpp ./scr/Game.cpp ./scr/Level.cpp ./scr/Player.cpp ./scr/Enemy.cpp ./scr/Bullet.cpp

LIBS = -lglut -lGLU -lGL -lpng

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG) 

