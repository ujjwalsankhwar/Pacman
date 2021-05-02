//
//  GameObject.hpp
//  MyGame
//
//  Created by Ujjwal Sankhwar on 29/04/21.
//

#ifndef GameObject_hpp
#define GameObject_hpp

#include "Game.hpp"

class GameObject{
public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();
    
    void Update();
    void Render();
    
private:
    int xpos;
    int ypos;
    
    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};

#endif /* GameObject_hpp */
