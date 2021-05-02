//
//  Collision.cpp
//  MyGame
//
//  Created by Ujjwal Sankhwar on 30/04/21.
//

#include "Collision.hpp"
#include "ColliderComponent.h"

bool Collision::AABB(const SDL_Rect &recA, const SDL_Rect &recB){
    if(recA.x+recA.w >= recB.x && recB.x+recB.w >= recA.x && recA.y+recA.h >= recB.y && recB.y+recB.h >= recA.y){
        return true;
    }
    return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB){
    if(AABB(colA.collider, colB.collider)){
        return true;
    }
    return false;
}
