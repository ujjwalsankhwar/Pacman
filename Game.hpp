//
//  Game.hpp
//  MyGame
//
//  Created by Ujjwal Sankhwar on 29/04/21.
//

#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <vector>

class AssetManager;
class ColliderComponent;

class Game{
public:
    Game();
    ~Game();
    
    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    
    bool running(){
        return isRunning;
    }
    
    bool pause(){
        return isPause;
    }
    
    static SDL_Renderer *renderer;
    static SDL_Event event;
    static AssetManager* assets;
    static bool isRunning;
    static bool isPause;
    
    enum groupLabels : std::size_t{
        groupMap,
        groupPacman,
        groupBlinky,
        groupColliders
    };
private:
    SDL_Window *window;
};

#endif /* Game_hpp */
