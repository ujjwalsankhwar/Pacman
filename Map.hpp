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
    Map();
    ~Map();
    
    static void LoadMap(std::string path, int sizeX, int sizeY);
    
private:
};

#endif /* Map_hpp */
