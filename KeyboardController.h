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
                case SDLK_UP:
                    transform->velocity.y = -1;
                    sprite->Play("Up");
                    break;
                case SDLK_a:
                case SDLK_LEFT:
                    transform->velocity.x = -1;
                    sprite->Play("Left");
                    break;
                case SDLK_d:
                case SDLK_RIGHT:
                    transform->velocity.x = 1;
                    sprite->Play("Right");
                    break;
                case SDLK_s:
                case SDLK_DOWN:
                    transform->velocity.y = 1;
                    sprite->Play("Down");
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
