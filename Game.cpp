//
//  Game.cpp
//  MyGame
//
//  Created by Ujjwal Sankhwar on 29/04/21.
//

#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Components.h"
#include "Vector2D.hpp"
#include "Collision.hpp"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& pacman(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t{
    groupMap,
    groupPacman,
    groupEnemies,
    groupColliders
};

Game::Game(){
    
}
Game::~Game(){
    
}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags=0;
    if(fullscreen){
        flags=SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING)==0){
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        isRunning=true;
        
        map = new Map();
        
        Map::LoadMap("/Users/ujjwalsankhwar/Desktop/MyGame/images/map.txt", 20, 15);
        
        pacman.addComponent<TransformComponent>();
        pacman.addComponent<SpriteComponent>("/Users/ujjwalsankhwar/Desktop/MyGame/images/pacman.png",true);
        pacman.addComponent<KeyboardController>();
        pacman.addComponent<ColliderComponent>("pacman");
        pacman.addGroup(groupPacman);
        
        wall.addComponent<TransformComponent>(300.0f,300.0f,300,20,1);
        wall.addComponent<SpriteComponent>("/Users/ujjwalsankhwar/Desktop/MyGame/images/Black.png");
        wall.addComponent<ColliderComponent>("wall");
        wall.addGroup(groupMap);
    }
    else{
        isRunning=false;
    }
}

void Game::handleEvents(){
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
            
        default:
            break;
    }
}

void Game::update(){
    manager.refresh();
    manager.update();
    
    for(auto cc : colliders){
        Collision::AABB(pacman.getComponent<ColliderComponent>(), *cc);
    }
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPacman));
auto& enemies(manager.getGroup(groupEnemies));

void Game::render(){
    SDL_RenderClear(renderer);
    for(auto& t : tiles){
        t->draw();
    }
    for(auto& p : players){
        p->draw();
    }
    for(auto& e : enemies){
        e->draw();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::AddTile(int id, int x, int y){
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x,y,40,40,id);
    tile.addGroup(groupMap);
}
