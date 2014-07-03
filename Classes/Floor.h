//
//  Floor.h
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#ifndef __MikuRun__Floor__
#define __MikuRun__Floor__

#include <iostream>
#include "Headers.h"

class Floor:public Sprite {
public:
    

    
    bool initFloor();
    CREATE_FUNC(Floor);
    static  Floor * createFloor();
};

#endif /* defined(__MikuRun__Floor__) */
