//
//  Map.cpp
//  MyGame
//
//  Created by Ujjwal Sankhwar on 29/04/21.
//

#include "Map.hpp"
#include "Game.hpp"
#include <fstream>
#include "ECS.hpp"
#include "Components.h"

extern Manager manager;

Map::Map(std::string tID, int tsize) : texID(tID), tileSize(tsize){
    
}

Map::~Map(){

}

void Map::LoadMap(std::string path, int sizeX, int sizeY){
    char c;
    std::fstream mapFile;
    mapFile.open(path);
    
    int src;
    for(int y=0;y<sizeY;y++){
        for(int x=0;x<sizeX;x++){
            mapFile.get(c);
            if(c == '0'){
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("wall", x*tileSize, y*tileSize, tileSize);
                tcol.addGroup(Game::groupColliders);
            }
            src = atoi(&c) * tileSize;
            AddTile(src, x*tileSize, y*tileSize);
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::AddTile(int src, int xpos, int ypos){
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(src, xpos, ypos, tileSize, texID);
    tile.addGroup(Game::groupMap);
}
