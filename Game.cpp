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
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "AssetManager.hpp"
#include <sstream>


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

AssetManager* Game::assets = new AssetManager(&manager);

bool Game::isRunning = false;
bool Game::isPause = false;

auto& pacman(manager.addEntity());
auto& blinky(manager.addEntity());
auto& timer(manager.addEntity());
auto& toBeat(manager.addEntity());
auto& map1(manager.addEntity());
auto& map2(manager.addEntity());
auto& map3(manager.addEntity());
auto& map4(manager.addEntity());
auto& map5(manager.addEntity());
auto& score(manager.addEntity());
auto& enter(manager.addEntity());
auto& result(manager.addEntity());

Mix_Chunk* intro;
Mix_Chunk* intermission;
Mix_Chunk* death;

Uint32 reset=0;
int stage=0;
int pacScore=0;
int blinkyScore=0;

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
        isPause=true;
        
    }
    if(TTF_Init()==-1){
        std::cout<<"Error : SDL_TTF"<<std::endl;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048)<0){
        std::cout<<"Error : SDL_Mixer"<<std::endl;
    }
    
    intro = Mix_LoadWAV("/Users/ujjwalsankhwar/Desktop/MyGame/Resources/intro.wav");
    intermission = Mix_LoadWAV("/Users/ujjwalsankhwar/Desktop/MyGame/Resources/intermission.wav");
    death = Mix_LoadWAV("/Users/ujjwalsankhwar/Desktop/MyGame/Resources/death.wav");
    Mix_PlayChannel(0, intro, -1);
    
    assets->AddTexture("mapTiles", "/Users/ujjwalsankhwar/Desktop/MyGame/Resources/map.png");
    assets->AddTexture("pacman", "/Users/ujjwalsankhwar/Desktop/MyGame/Resources/pacman.png");
    assets->AddTexture("blinky", "/Users/ujjwalsankhwar/Desktop/MyGame/Resources/Blinky.png");
    assets->AddFont("comic", "/Users/ujjwalsankhwar/Desktop/MyGame/Resources/Comic Sans MS.ttf", 20);
    assets->AddFont("arial", "/Users/ujjwalsankhwar/Desktop/MyGame/Resources/arial.ttf", 25);
    
    pacman.addComponent<TransformComponent>(452,502,0);
    pacman.addComponent<SpriteComponent>("pacman", true);
    pacman.addComponent<KeyboardController>();
    pacman.addComponent<ColliderComponent>("pacman");
    pacman.addGroup(groupPacman);
    
    blinky.addComponent<TransformComponent>(252,252,1);
    blinky.addComponent<SpriteComponent>("blinky",true);
    blinky.addComponent<KeyboardController>();
    blinky.addComponent<ColliderComponent>("blinky");
    blinky.addGroup(groupBlinky);
    
    SDL_Color white = {255,255,255,255};
    timer.addComponent<UILabel>(25, 548, "test", "comic", white);
    toBeat.addComponent<UILabel>(350, 548, "test", "comic", white);
    map1.addComponent<UILabel>(160,205,"Press 1 for Map 1","arial",white);
    map2.addComponent<UILabel>(160,240,"Press 2 for Map 2","arial",white);
    map3.addComponent<UILabel>(160,275,"Press 3 for Map 3","arial",white);
    map4.addComponent<UILabel>(160,310,"Press 4 for Map 4","arial",white);
    map5.addComponent<UILabel>(160,345,"Press 5 for Map 5","arial",white);
    score.addComponent<UILabel>(160,245,"test","arial",white);
    result.addComponent<UILabel>(185,290,"test","arial",white);
    enter.addComponent<UILabel>(187,355,"Press Enter","arial",white);
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
    if(isPause==true && Game::event.type == SDL_KEYDOWN){
        if(stage==0){
            blinkyScore = pacScore = 0;
            switch (Game::event.key.keysym.sym){
                case SDLK_1:
                    map = new Map("mapTiles", 25);
                    map->LoadMap("/Users/ujjwalsankhwar/Desktop/MyGame/Resources/map.txt", 20, 25);
                    isPause=false;
                    stage=stage+1;
                    Mix_HaltChannel(0);
                    break;
                case SDLK_2:
                    map = new Map("mapTiles", 25);
                    map->LoadMap("/Users/ujjwalsankhwar/Desktop/MyGame/Resources/map_2.txt", 20, 25);
                    isPause=false;
                    stage=stage+1;
                    Mix_HaltChannel(0);
                    break;
                case SDLK_3:
                    map = new Map("mapTiles", 25);
                    map->LoadMap("/Users/ujjwalsankhwar/Desktop/MyGame/Resources/map_3.txt", 20, 25);
                    isPause=false;
                    stage=stage+1;
                    Mix_HaltChannel(0);
                    break;
                case SDLK_4:
                    map = new Map("mapTiles", 25);
                    map->LoadMap("/Users/ujjwalsankhwar/Desktop/MyGame/Resources/map_4.txt", 20, 25);
                    isPause=false;
                    stage=stage+1;
                    Mix_HaltChannel(0);
                    break;
                case SDLK_5:
                    map = new Map("mapTiles", 25);
                    map->LoadMap("/Users/ujjwalsankhwar/Desktop/MyGame/Resources/map_5.txt", 20, 25);
                    isPause=false;
                    stage=stage+1;
                    Mix_HaltChannel(0);
                    break;
                default:
                    break;
            }
        }
        else if(stage==1){
            switch (Game::event.key.keysym.sym){
                case SDLK_RETURN:
                    stage=2;
                    isPause=false;
                    Mix_HaltChannel(2);
                    break;
                default:
                    break;
            }
        }
        else if(stage==2){
            switch (Game::event.key.keysym.sym){
                case SDLK_RETURN:
                    stage=0;
                    isPause=true;
                    Mix_HaltChannel(2);
                    Mix_PlayChannel(0, intro, -1);
                    break;
                default:
                    break;
            }
        }
    }
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPacman));
auto& enemies(manager.getGroup(Game::groupBlinky));
auto& colliders(manager.getGroup(Game::groupColliders));

void Game::update(){
    
    SDL_Rect pacmanCol = pacman.getComponent<ColliderComponent>().collider;
    Vector2D pacmanPos = pacman.getComponent<TransformComponent>().position;
    
    SDL_Rect blinkyCol = blinky.getComponent<ColliderComponent>().collider;
    Vector2D blinkyPos = blinky.getComponent<TransformComponent>().position;
    
    if(isPause==true){
        reset=SDL_GetTicks();
        std::stringstream ss;
        if(stage==1){
            ss << "Pacman Score : " << pacScore;
            score.getComponent<UILabel>().SetLabelText(ss.str(), "arial");
        }
        if(stage==2){
            ss << "Blinky Score : " << blinkyScore;
            score.getComponent<UILabel>().SetLabelText(ss.str(), "arial");
            if(blinkyScore>pacScore){
                result.getComponent<UILabel>().SetLabelText("Blinky Won", "arial");
            }
            if(blinkyScore<pacScore){
                result.getComponent<UILabel>().SetLabelText("Pacman Won", "arial");
            }
            if(blinkyScore==pacScore){
                result.getComponent<UILabel>().SetLabelText("Match Tied", "arial");
            }
            
        }
    }
    if(isPause==false){
        std::stringstream ss;
        ss << "Time : " << int((SDL_GetTicks()-reset)/1000);
        if(stage==1){
            pacScore=int((SDL_GetTicks()-reset)/1000);
            toBeat.getComponent<UILabel>().SetLabelText("To Beat : "+std::to_string(pacScore), "comic");
        }
        if(stage==2){
            blinkyScore=int((SDL_GetTicks()-reset)/1000);
        }
        timer.getComponent<UILabel>().SetLabelText(ss.str(), "comic");
    }
    
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
        pacman.getComponent<TransformComponent>().position.x = 452;
        pacman.getComponent<TransformComponent>().velocity.x=0;
        pacman.getComponent<TransformComponent>().position.y = 502;
        pacman.getComponent<TransformComponent>().velocity.y=0;
        blinky.getComponent<TransformComponent>().position.x = 252;
        blinky.getComponent<TransformComponent>().velocity.x=0;
        blinky.getComponent<TransformComponent>().position.y = 252;
        blinky.getComponent<TransformComponent>().velocity.y=0;
        isPause = true;
        Mix_PlayChannel(1, death, 0);
        Mix_PlayChannelTimed(2, intermission, -1, SDL_GetTicks()+2000);
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
    if(isPause==true){
        SDL_Texture* tex = TextureManager::LoadTexture("/Users/ujjwalsankhwar/Desktop/MyGame/Resources/Background.bmp");
        SDL_RenderCopy(renderer, tex, NULL, NULL);
        if(stage==0){
            map1.draw();
            map2.draw();
            map3.draw();
            map4.draw();
            map5.draw();
        }
        if(stage==1){
            score.draw();
            enter.draw();
        }
        if(stage==2){
            score.draw();
            result.draw();
            enter.draw();
        }
    }
    if(isPause==false){
        for(auto& t : tiles){
            t->draw();
        }
        for(auto& p : players){
            p->draw();
        }
        for(auto& e : enemies){
            e->draw();
        }
        timer.draw();
        if(stage==2){
            toBeat.draw();
        }
    }
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
