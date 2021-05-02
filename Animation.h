//
//  Animation.h
//  MyGame
//
//  Created by Ujjwal Sankhwar on 01/05/21.
//

#ifndef Animation_h
#define Animation_h

struct Animation{
    int index;
    int frames;
    int speed;
    
    Animation(){
        
    }
    Animation(int i ,int f, int s){
        index=i;
        frames=f;
        speed=s;
    }
};


#endif /* Animation_h */
