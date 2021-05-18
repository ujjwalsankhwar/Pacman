//
//  AssetManager.cpp
//  MyGame
//
//  Created by Ujjwal Sankhwar on 18/05/21.
//

#include "AssetManager.hpp"

AssetManager::AssetManager(Manager* man) : manager(man){
    
}

AssetManager::~AssetManager(){
    
}

void AssetManager::AddTexture(std::string id, const char* path){
    texture.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id){
    return texture[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize){
    fonts.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id){
    return fonts[id];
}
