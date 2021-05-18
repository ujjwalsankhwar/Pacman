//
//  TileComponent.h
//  MyGame
//
//  Created by Ujjwal Sankhwar on 30/04/21.
//

#ifndef TileComponent_h
#define TileComponent_h

#include "ECS.hpp"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include <SDL2/SDL.h>

class TileComponent : public Component{
public:
    
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    
    TileComponent() = default;
    
    ~TileComponent(){
        SDL_DestroyTexture(texture);
    }
    
    TileComponent(int src, int xpos, int ypos, int tsize, const char* path){
        texture = TextureManager::LoadTexture(path);
        srcRect.x = src;
        srcRect.y = 0;
        srcRect.w = srcRect.h = tsize;
        
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = tsize;
    }
    
    void draw() override{
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};

#endif /* TileComponent_h */