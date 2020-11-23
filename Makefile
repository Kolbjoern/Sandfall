CPP=g++
FLAGS=-Wall -Iinclude -Llibs
FILES=src/main.cpp src/Game.cpp src/grids/GridManager.cpp src/grids/GridQuad.cpp src/grids/GridRect.cpp src/grids/GridNull.cpp src/utils/LoopTimer.cpp
LIBS=-lsfml-system -lsfml-window -lsfml-graphics -lsfml-network

Game: src/main.cpp
	$(CPP) $(FLAGS) -o release/sandfall -g $(FILES) $(LIBS)