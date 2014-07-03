//
//  ScoreScene.h
//  MikuRun
//
//  Created by the9 on 14-6-24.
//
//

#ifndef __MikuRun__ScoreScene__
#define __MikuRun__ScoreScene__

#include <iostream>
#include "Headers.h"
class ScoreScene:public Layer {
    
private:
    //菜单项返回主菜单的回调函数
    void backMenu(Ref *ref);
public:
    virtual bool init();
    static Scene*scene();
    CREATE_FUNC(ScoreScene);
};


#endif /* defined(__MikuRun__ScoreScene__) */
