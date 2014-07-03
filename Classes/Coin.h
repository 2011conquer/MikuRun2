//
//  Coin.h
//  MikuRun
//
//  Created by the9 on 14-6-24.
//
//

#ifndef __MikuRun__Coin__
#define __MikuRun__Coin__

#include <iostream>
#include "Headers.h"

class Coin:public Sprite {
public:
    
    static Coin * createCoin();
    
    bool init();
   
    void runAnimateAndStopFrame(int startframe,int stopframe);
};

#endif /* defined(__MikuRun__Coin__) */
