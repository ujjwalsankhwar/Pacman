//
//  TransformComponent.h
//  MyGame
//
//  Created by Ujjwal Sankhwar on 30/04/21.
//

#ifndef TransformComponent_h
#define TransformComponent_h

#include "Components.h"
#include "Vector2D.hpp"

struct TransformComponent : public Component{
public:
    Vector2D position;
    Vector2D velocity;
    
    int height = 40;
    int width = 40;
    int scale = 1;
    
    int speed = 3;
    
    
    TransformComponent(){
        position.Zero();
    }
    TransformComponent(int sc){
        position.Zero();
        scale = sc;
    }
    TransformComponent(float x, float y){
        position.Zero();
    }
    TransformComponent(float x, float y, int h, int w, int sc){
        position.x=x;
        position.y=y;
        width=w;
        height=h;
        scale=sc;
    }
    
    void init() override{
        velocity.Zero();
    }
    void update() override{
        position.x += velocity.x*speed;
        position.y += velocity.y*speed;
    }
};

#endif /* TransformComponent_h */
