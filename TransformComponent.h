//
//  TransformComponent.h
//  MyGame
//
//

#ifndef TransformComponent_h
#define TransformComponent_h

#include "Components.h"
#include "Vector2D.hpp"

struct TransformComponent : public Component{
public:
    Vector2D position;
    Vector2D velocity;
    
    int height = 20;
    int width = 20;
    int scale = 1;
    int id=0;
    int speed = 2;
    
    
    TransformComponent(){
        position.Zero();
    }
    TransformComponent(int sc){
        position.Zero();
        scale = sc;
    }
    TransformComponent(float x, float y, int i){
        position.x=x;
        position.y=y;
        id=i;
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
