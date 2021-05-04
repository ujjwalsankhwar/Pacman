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
    Map(int tsize);
    ~Map();
    
    void LoadMap(std::string path, int sizeX, int sizeY);
    void AddTile(int id, int x, int y);
    
private:
    const char* mapFilePath;
    int mapScale;
    int tileSize;
};

#endif /* Map_hpp */
