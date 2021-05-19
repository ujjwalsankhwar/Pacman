//
//  ColliderComponent.h
//  MyGame
//
//

#ifndef ColliderComponent_h
#define ColliderComponent_h

#include <string>
#include <SDL2/SDL.h>
#include "ECS.hpp"
#include "Components.h"
#include "TextureManager.hpp"

class ColliderComponent : public Component{
public:
    SDL_Rect collider;
    std::string tag;
    
    SDL_Texture* tex;
    SDL_Rect srcR, destR;
    
    TransformComponent* transform;
    
    ColliderComponent(std::string t){
        tag = t;
    }
    
    ColliderComponent(std::string t, int xpos, int ypos, int size){
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
        
    }
    
    void init() override{
        if(!entity->hasComponent<TransformComponent>()){
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
        
        tex = TextureManager::LoadTexture("/Users/ujjwalsankhwar/Desktop/MyGame/images/Blue.png");
        srcR = {0,0,25,25};
        destR = {collider.x, collider.y, collider.w, collider.h};
        
    }
    
    void update() override{
        if(tag != "wall"){
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }
    }
    
    void draw() override{
        TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
};

#endif /* ColliderComponent_h */
