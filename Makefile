all: main.cpp
	g++ -g3 -lSDL2 -lSDL2_ttf -lSDL2_mixer -o main main.cpp
