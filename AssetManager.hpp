//
//  AssetManager.hpp
//  MyGame
//
//  Created by Ujjwal Sankhwar on 18/05/21.
//

#ifndef AssetManager_hpp
#define AssetManager_hpp

#include <map>
#include <string>
#include "TextureManager.hpp"
#include "Vector2D.hpp"
#include "ECS.hpp"
#include <SDL2/SDL_ttf.h>

class AssetManager{
public:
    AssetManager(Manager* man);
    ~AssetManager();
    
    void AddTexture(std::string id, const char* path);
    SDL_Texture* GetTexture(std::string id);
    void AddFont(std::string id, std::string path, int fontSize);
    TTF_Font* GetFont(std::string id);
    
private:
    Manager* manager;
    std::map<std::string, SDL_Texture*> texture;
    std::map<std::string, TTF_Font*> fonts;
};

#endif /* AssetManager_hpp */
