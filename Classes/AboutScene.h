//
//  AboutScene.h
//  MikuRun
//
//  Created by the9 on 14-6-24.
//
//

#ifndef __MikuRun__AboutScene__
#define __MikuRun__AboutScene__

#include <iostream>
#include "Headers.h"

class AboutScene:public Layer {
    
private:
    //菜单项返回主菜单的回调函数
    void backMenu(Ref *ref);
public:
    virtual bool init();
    static Scene*scene();
    CREATE_FUNC(AboutScene);
};

#endif /* defined(__MikuRun__AboutScene__) */
