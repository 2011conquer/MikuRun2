//
//  PowerBar.h
//  MikuRun
//
//  Created by the9 on 14-6-24.
//
//

#ifndef __MikuRun__PowerBar__
#define __MikuRun__PowerBar__

#include <iostream>
#include "Headers.h"

class PowerBar:public Layer {

public:
    //用来保存游戏需要加载的资源总数
    int sourceCount;
    int numLoaded;//已经加载的资源总数
    //进度条
    ProgressTimer *progress;
    //代表进度条更新的次数
    float progressInterval;
    
    virtual bool init();
    
    void loadingComplete();//资源全部加载完成，切换到另一个游戏场景
    void progressUpdate();//更新游戏进度条
};


#endif /* defined(__MikuRun__PowerBar__) */
