//
//  GameObject.cpp
//  MyGame
//
//  Created by Ujjwal Sankhwar on 29/04/21.
//

#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y){
    objTexture = TextureManager::LoadTexture(texturesheet);
    
    xpos=x;
    ypos=y;
}

void GameObject::Update(){
    xpos++;
    ypos++;
    
    srcRect.h = 40;
    srcRect.w = 40;
    srcRect.x = 0;
    srcRect.y = 0;
    
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
    
}

void GameObject::Render(){
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
