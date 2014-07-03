//
//  Floor.cpp
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#include "Floor.h"

bool Floor::initFloor()
{
    
    
    return true;
}

Floor * Floor::createFloor()
{
    Floor *floor = new Floor();
    if (floor && floor->initWithFile("floor1.png")) {
        
        floor->autorelease();
        
   //     floor->initFloor();
        
        return floor;
    }
    
    CC_SAFE_DELETE(floor);
    return NULL;
}