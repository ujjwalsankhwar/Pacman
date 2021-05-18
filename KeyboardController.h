//
//  KeyboardController.h
//  MyGame
//
//  Created by Ujjwal Sankhwar on 30/04/21.
//

#ifndef KeyboardController_h
#define KeyboardController_h

#include "Game.hpp"
#include "ECS.hpp"
#include "Components.h"

class KeyboardController : public Component{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    
    void init() override{
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }
    void update() override{
        if(Game::event.type == SDL_KEYDOWN){
            switch (Game::event.key.keysym.sym){
                case SDLK_w:
                    if(transform->id==1){
                        transform->velocity.y = -1;
                        sprite->Play("blinkyUp");
                    }
                    break;
                case SDLK_UP:
                    if(transform->id==0){
                        transform->velocity.y = -1;
                        sprite->Play("pacUp");
                    }
                    break;
                case SDLK_a:
                    if(transform->id==1){
                        transform->velocity.x = -1;
                        sprite->Play("blinkyLeft");
                    }
                    break;
                case SDLK_LEFT:
                    if(transform->id==0){
                        transform->velocity.x = -1;
                        sprite->Play("pacLeft");
                    }
                    break;
                case SDLK_d:
                    if(transform->id==1){
                        transform->velocity.x = 1;
                        sprite->Play("blinkyRight");
                    }
                    break;
                case SDLK_RIGHT:
                    if(transform->id==0){
                        transform->velocity.x = 1;
                        sprite->Play("pacRight");
                    }
                    break;
                case SDLK_s:
                    if(transform->id==1){
                        transform->velocity.y = 1;
                        sprite->Play("blinkyDown");
                    }
                    break;
                case SDLK_DOWN:
                    if(transform->id==0){
                        transform->velocity.y = 1;
                        sprite->Play("pacDown");
                    }
                    break;
                case SDLK_ESCAPE:
                    Game::isRunning = false;
                default:
                    break;
            }
        }
       /* if(Game::event.type == SDL_KEYUP){
            switch (Game::event.key.keysym.sym){
                case SDLK_w:
                    transform->velocity.y = 0;
                    break;
                case SDLK_a:
                    transform->velocity.x = 0;
                    break;
                case SDLK_d:
                    transform->velocity.x = 0;
                    break;
                case SDLK_s:
                    transform->velocity.y = 0;
                    break;
                default:
                    break;
            }
        }*/
    }
};

#endif /* KeyboardController_h */
