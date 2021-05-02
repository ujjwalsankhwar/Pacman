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
    TransformComponent *transform;
    SpriteComponent *sprite;
    
    SDL_Rect tileRect;
    int tileID;
    char* path;
    
    TileComponent() = default;
    
    TileComponent(int x, int y, int w, int h, int id){
        tileRect.x=x;
        tileRect.y=y;
        tileRect.w=w;
        tileRect.h=h;
        tileID=id;
        
        switch (tileID){
            case 0:
                path = "/Users/ujjwalsankhwar/Desktop/MyGame/images/Blue.png";
                break;
            case 1:
                path = "/Users/ujjwalsankhwar/Desktop/MyGame/images/Black.png";
                break;
            default:
                break;
        }
    }
    
    void init() override{
        entity->addComponent<TransformComponent>((float)tileRect.x,(float)tileRect.y,tileRect.w,tileRect.h,1);
        transform = &entity->getComponent<TransformComponent>();
        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
};

#endif /* TileComponent_h */
