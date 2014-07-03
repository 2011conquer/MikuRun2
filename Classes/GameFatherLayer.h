//
//  GameFatherLayer.h
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#ifndef __MikuRun__GameFatherLayer__
#define __MikuRun__GameFatherLayer__

#include <iostream>
#include "Headers.h"
class GameFatherLayer:public Layer{
    
public:
    CREATE_FUNC(GameFatherLayer);
    
    static Scene *scene();
    
    static bool allowSound();
    
    void initUI();
    
    virtual bool init();
private:
    
    MenuItemImage *soundItem;
    
    void startGame(Ref *sender);
    
    void aboutGame(Ref *sender);

    void scoreGame(Ref *sender);
    
    void soundSwitch(Ref *sender);

};


#endif /* defined(__MikuRun__GameFatherLayer__) */
