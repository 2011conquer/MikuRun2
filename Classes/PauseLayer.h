//
//  PauseLayer.h
//  MikuRun
//
//  Created by 程龙元 on 14-6-29.
//
//

#ifndef __MikuRun__PauseLayer__
#define __MikuRun__PauseLayer__

#include <iostream>
#include "Headers.h"
class PauseLayer:public Layer
{
public:
    CREATE_FUNC(PauseLayer);
    
    bool init();
    
    void backToGame(Ref *ref);
    void backToMenu(Ref *ref);
};

#endif /* defined(__MikuRun__PauseLayer__) */
