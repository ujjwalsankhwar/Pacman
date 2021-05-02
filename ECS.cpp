//
//  ECS.cpp
//  MyGame
//
//  Created by Ujjwal Sankhwar on 29/04/21.
//

#include "ECS.hpp"

void Entity::addGroup(Group mGroup){
    groupBitSet[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}
