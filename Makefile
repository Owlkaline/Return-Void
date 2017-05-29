OBJS = $(SRCMAIN) $(SRCMENU) $(SRCGAME) $(SRCSTORY) $(SRCENEMIES) $(SRCMOUNTS) $(SRCBULLETS) $(SRCDROPS)

SRCMAIN =./src/main.cpp ./src/GraphicsHandler.cpp ./src/Namespaces/LoadTexture.cpp ./src/Namespaces/Collisions.cpp ./src/Namespaces/Random.cpp ./src/Namespaces/File.cpp ./src/Namespaces/Movement.cpp ./src/Namespaces/Settings.cpp ./src/Namespaces/Profile.cpp ./src/Namespaces/Highscore.cpp ./src/Ships/GalacticShip.cpp ./src/Ships/FighterShip.cpp ./src/Ships/HeroShip3.cpp

SRCMENU =./src/Menus/SettingsMenu.cpp ./src/Menus/PausedMenu.cpp ./src/Menus/Button.cpp ./src/Menus/Label.cpp ./src/Menus/CheckBox.cpp ./src/Menus/HighscoreScreen.cpp ./src/Menus/Shop.cpp ./src/Menus/Shipbox.cpp ./src/Menus/FloatingText.cpp ./src/Menus/Text.cpp

SRCSTORY =./src/Story/StarMap.cpp

SRCGAME =./src/GameTypes/Game.cpp ./src/Menus/MainMenu.cpp ./src/Misc/Effects.cpp ./src/Misc/SmallExplosion.cpp ./src/GameTypes/Story.cpp

SRCENEMIES =./src/Enemies/BasicEnemy.cpp ./src/Enemies/CorruptedStarShip.cpp ./src/Enemies/HypnoEnemy.cpp ./src/Enemies/AlphaOne.cpp ./src/Enemies/DotEnemy.cpp

SRCMOUNTS =./src/Mounts/BasicMount.cpp ./src/Mounts/TriangleMount.cpp ./src/Mounts/HypnoMount.cpp ./src/Mounts/PurpleMount.cpp ./src/Mounts/AlphaOneMount.cpp ./src/Mounts/DotMount.cpp ./src/Mounts/MountType1.cpp ./src/Mounts/MountType2.cpp ./src/Mounts/MountType3.cpp

SRCBULLETS =./src/Weapons/RedPlasma.cpp ./src/Weapons/BluePlasma.cpp  ./src/Weapons/GreenPlasma.cpp ./src/Weapons/PurplePlasma.cpp ./src/Weapons/Spiral.cpp ./src/Weapons/AlphaOnePlasma.cpp ./src/Weapons/DotBullet.cpp

SRCDROPS =./src/Drops/Coins.cpp ./src/Drops/Health.cpp ./src/Drops/Shield.cpp

OS := $(shell uname)
CC = g++ -O3 -g

COMPILER_FLAGS = -I./staticlibs/ -std=c++14

ifeq ($(OS), Darwin)
INCLUDE_PATHS = -I/usr/local/include
LIBRARY_PATHS = -L/usr/local/lib


LINKER_FLAGS = -lglew -lglfw -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

else

ifeq ($(OS), Linux)
INCLUDE_PATHS =  -I/usr/include -I/usr/include/freetype2
LIBRARY_PATHS =  -L/usr/lib

LINKER_FLAGS = -lGL -lglfw -lGLEW -lfreetype

else
INCLUDE_PATHS = -I./win32/include
LIBRARY_PATHS = -L./win32/lib

LINKER_FLAGS = -lmingw32 -lopengl32 -lglew32.dll -lglfw3 -lfreetype -luser32 -lgdi32 -lkernel32 -D_USE_MATH_DEFINES

endif
endif



OBJ_NAME = Return-void

all: $(OBJS)
				$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
				
