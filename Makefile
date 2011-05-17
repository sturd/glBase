app_name = base

all: gfx

gfx: tga.o sprite.o leveldata.o
	g++ -o $(app_name) -lGL -lSDL -lSDL_mixer tga.o sprite.o leveldata.o main.cpp
	
tga.o: src/sprite/tga.cpp
	g++ -c src/sprite/tga.cpp
	
sprite.o: tga.o src/sprite/sprite.cpp
	g++ -c src/sprite/sprite.cpp
	
leveldata.o: sprite.o src/env/leveldata.cpp
	g++ -c src/env/leveldata.cpp
	
clean:
	rm -rf *.o $(app_name)
