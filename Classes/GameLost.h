//
//  GameLost.h
//  MikuRun
//
//  Created by the9 on 14-6-24.
//
//

#ifndef __MikuRun__GameLost__
#define __MikuRun__GameLost__

#include <iostream>
#include "Headers.h"

class GameLost:public Layer {

public:
    //菜单项返回主菜单的回调函数
    void backMenu(Ref *ref);
    void resetButton(Ref *ref);
    
    virtual bool init();
    static Scene*scene();
    CREATE_FUNC(GameLost);
    
};


#endif /* defined(__MikuRun__GameLost__) */
