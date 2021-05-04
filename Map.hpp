//
//  Map.hpp
//  MyGame
//
//  Created by Ujjwal Sankhwar on 29/04/21.
//

#ifndef Map_hpp
#define Map_hpp

#include <string>

class Map{
public:
    Map(const char* mapFile, int tsize);
    ~Map();
    
    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int src, int xpos, int ypos);
    
private:
    const char* mapFilePath;
    int tileSize;
};

#endif /* Map_hpp */
