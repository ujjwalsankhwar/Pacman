make all:
	g++ main.cpp Game.cpp TextureManager.cpp Collision.cpp ECS.cpp GameObject.cpp Map.cpp Vector2D.cpp AssetManager.cpp -o out -pthread -std=c++11 `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

