all:
	g++ src/main.cpp src/RenderManager.cpp `sdl-config --cflags` -I include -o debug/prog -lSDL2main -lSDL2 -lSDL2_image