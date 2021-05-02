//
//  SpriteComponent.h
//  MyGame
//
//  Created by Ujjwal Sankhwar on 30/04/21.
//

#ifndef SpriteComponent_h
#define SpriteComponent_h

#include "Components.h"
#include <SDL2/SDL.h>
#include "TextureManager.hpp"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect,destRect;
    
    bool animated = false;
    int frames = 0;
    int speed = 100;
    
public:
    int animIndex=0;
    
    std::map<const char*, Animation> animations;
    
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    
    SpriteComponent() = default;
    SpriteComponent(const char* path){
        setTex(path);
    }
    
    SpriteComponent(const char* path, bool isAnimated){
        animated = isAnimated;
        
        Animation pacRight = Animation(0,14,25);
        Animation pacUp = Animation(14,14,25);
        Animation pacLeft = Animation(28,14,25);
        Animation pacDown = Animation(42,14,25);
        
        animations.emplace("pacRight",pacRight);
        animations.emplace("pacUp",pacUp);
        animations.emplace("pacLeft",pacLeft);
        animations.emplace("pacDown",pacDown);
        
        Play("pacRight");
        
        setTex(path);
    }
    
    ~SpriteComponent(){
        SDL_DestroyTexture(texture);
    }
    
    void setTex(const char* path){
        texture = TextureManager::LoadTexture(path);
    }
    
    void init() override{
        transform = &entity->getComponent<TransformComponent>();
        
        srcRect.x = animIndex * transform->width;
        srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }
    void update() override{
        
        if(animated){
            srcRect.x = (animIndex*srcRect.w)+(srcRect.w * static_cast<int>((SDL_GetTicks()/speed)%frames));
        }
        
        destRect.x = static_cast<int>(transform->position.x);
        destRect.y = static_cast<int>(transform->position.y);
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->height * transform->scale;
    }
    void draw() override{
        TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
    }
    void Play(const char* animName){
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};

#endif /* SpriteComponent_h */
