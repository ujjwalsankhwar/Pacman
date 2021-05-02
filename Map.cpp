//
//  Map.cpp
//  MyGame
//
//  Created by Ujjwal Sankhwar on 29/04/21.
//

#include "Map.hpp"
#include "Game.hpp"
#include <fstream>

Map::Map(){
    
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
            Game::AddTile(atoi(&tile), x*40, y*40);
            mapFile.ignore();
        }
    }
    
    mapFile.close();
}
