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

Map::Map(int tsize) : tileSize(tsize){
    
}

Map::~Map(){

}

void Map::LoadMap(std::string path, int sizeX, int sizeY){
    char tile;
    std::fstream mapFile;
    mapFile.open(path);
    
    for(int y=0;y<sizeY;y++){
        for(int x=0;x<sizeX;x++){
            mapFile.get(tile);
            if(tile == '0'){
                auto& tcol(manager.addEntity());
                tcol.addComponent<ColliderComponent>("wall", x*tileSize, y*tileSize, tileSize);
                tcol.addGroup(Game::groupColliders);
            }
            AddTile(atoi(&tile), x*tileSize, y*tileSize);
            mapFile.ignore();
        }
    }
    mapFile.close();
}

void Map::AddTile(int id, int x, int y){
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x,y,tileSize,tileSize,id);
    tile.addGroup(Game::groupMap);
}
