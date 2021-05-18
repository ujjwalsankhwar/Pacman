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
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <vector>

/*struct data{
    TCPsocket socket;
    Uint32 timeout;
    int id;
    
    data(TCPsocket sock, Uint32 t, int i){
        socket = sock;
        timeout = t;
        id = i;
    }
};
*/
Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

bool Game::isRunning = false;

auto& pacman(manager.addEntity());
auto& blinky(manager.addEntity());

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
        
        map = new Map("/Users/ujjwalsankhwar/Desktop/MyGame/images/Map.png",25);
        map->LoadMap("/Users/ujjwalsankhwar/Desktop/MyGame/images/map.txt", 20, 25);
        
        pacman.addComponent<TransformComponent>(452,502);
        pacman.addComponent<SpriteComponent>("/Users/ujjwalsankhwar/Desktop/MyGame/images/pacman.png", 0, true);
     //   pacman.addComponent<KeyboardController>();
        pacman.addComponent<ColliderComponent>("pacman");
        pacman.addGroup(groupPacman);
        
        blinky.addComponent<TransformComponent>(252,252);
        blinky.addComponent<SpriteComponent>("/Users/ujjwalsankhwar/Desktop/MyGame/images/Blinky.png",1,true);
        blinky.addComponent<KeyboardController>();
        blinky.addComponent<ColliderComponent>("blinky");
        blinky.addGroup(groupBlinky);
        
    }
    else{
        isRunning=false;
    }
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPacman));
auto& enemies(manager.getGroup(Game::groupBlinky));
auto& colliders(manager.getGroup(Game::groupColliders));

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
    SDL_Rect pacmanCol = pacman.getComponent<ColliderComponent>().collider;
    Vector2D pacmanPos = pacman.getComponent<TransformComponent>().position;
    
    SDL_Rect blinkyCol = blinky.getComponent<ColliderComponent>().collider;
    Vector2D blinkyPos = blinky.getComponent<TransformComponent>().position;
    
    manager.refresh();
    manager.update();

    if(pacmanPos.x == -24){
        pacman.getComponent<TransformComponent>().position.x = 522;
    }
    if(pacmanPos.x == 524){
        pacman.getComponent<TransformComponent>().position.x = -22;
    }
    if(pacmanPos.y == -24){
        pacman.getComponent<TransformComponent>().position.y = 572;
    }
    if(pacmanPos.y == 574){
        pacman.getComponent<TransformComponent>().position.y = -22;
    }
    
    if(blinkyPos.x == -24){
        blinky.getComponent<TransformComponent>().position.x = 522;
    }
    if(blinkyPos.x == 524){
        blinky.getComponent<TransformComponent>().position.x = -22;
    }
    if(blinkyPos.y == -24){
        blinky.getComponent<TransformComponent>().position.y = 572;
    }
    if(blinkyPos.y == 574){
        blinky.getComponent<TransformComponent>().position.y = -22;
    }
    
    if(Collision::AABB(blinkyCol, pacmanCol) == true){
        isRunning = false;
    }
    
    for(auto c : colliders){
        SDL_Rect cCol = c->getComponent<ColliderComponent>().collider;
        if(Collision::AABB(cCol, pacmanCol) == true){
            
            SDL_Rect tmpCol;
            tmpCol.x = pacmanCol.x;
            tmpCol.y = pacmanCol.y;
            tmpCol.w = pacmanCol.w;
            tmpCol.h = pacmanCol.h;
            
            bool collide = true;
            tmpCol.x = pacmanCol.x+2;
            if(collide == true){
                if(Collision::AABB(cCol, tmpCol) == false){
                    pacman.getComponent<TransformComponent>().position.x = pacmanPos.x + 2;
                    pacman.getComponent<TransformComponent>().velocity.x=0;
                    collide = false;
                }
            }
            tmpCol.x = pacmanCol.x-2;
            if(collide == true){
                if(Collision::AABB(cCol, tmpCol) == false){
                    pacman.getComponent<TransformComponent>().position.x = pacmanPos.x - 2;
                    pacman.getComponent<TransformComponent>().velocity.x=0;
                    collide = false;
                }
            }
            tmpCol.y = pacmanCol.y+2;
            if(collide == true){
                if(Collision::AABB(cCol, tmpCol) == false){
                    pacman.getComponent<TransformComponent>().position.y = pacmanPos.y + 2;
                    pacman.getComponent<TransformComponent>().velocity.y=0;
                    collide = false;
                }
            }
            tmpCol.y = pacmanCol.y-2;
            if(collide == true){
                if(Collision::AABB(cCol, tmpCol) == false){
                    pacman.getComponent<TransformComponent>().position.y = pacmanPos.y - 2;
                    pacman.getComponent<TransformComponent>().velocity.y=0;
                    collide = false;
                }
            }
        }
        
        if(Collision::AABB(cCol, blinkyCol) == true){
            
            SDL_Rect tmpCol;
            tmpCol.x = blinkyCol.x;
            tmpCol.y = blinkyCol.y;
            tmpCol.w = blinkyCol.w;
            tmpCol.h = blinkyCol.h;
            
            bool collide = true;
            tmpCol.x = blinkyCol.x+2;
            if(collide == true){
                if(Collision::AABB(cCol, tmpCol) == false){
                    blinky.getComponent<TransformComponent>().position.x = blinkyPos.x + 2;
                    blinky.getComponent<TransformComponent>().velocity.x=0;
                    collide = false;
                }
            }
            tmpCol.x = blinkyCol.x-2;
            if(collide == true){
                if(Collision::AABB(cCol, tmpCol) == false){
                    blinky.getComponent<TransformComponent>().position.x = blinkyPos.x - 2;
                    blinky.getComponent<TransformComponent>().velocity.x=0;
                    collide = false;
                }
            }
            tmpCol.y = blinkyCol.y+2;
            if(collide == true){
                if(Collision::AABB(cCol, tmpCol) == false){
                    blinky.getComponent<TransformComponent>().position.y = blinkyPos.y + 2;
                    blinky.getComponent<TransformComponent>().velocity.y=0;
                    collide = false;
                }
            }
            tmpCol.y = blinkyCol.y-2;
            if(collide == true){
                if(Collision::AABB(cCol, tmpCol) == false){
                    blinky.getComponent<TransformComponent>().position.y = blinkyPos.y - 2;
                    blinky.getComponent<TransformComponent>().velocity.y=0;
                    collide = false;
                }
            }
        }
    }
}

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
