//
//  PreloadLayer.h
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#ifndef __MikuRun__PreloadLayer__
#define __MikuRun__PreloadLayer__

#include <iostream>
#include "Headers.h"

class PreloadLayer:public Layer
{
public:
    //用来保存游戏需要加载的资源总数
    int sourceCount;
    int numLoaded;//已经加载的资源总数
    //进度条
    ProgressTimer *progress;
    //代表进度条更新的次数
    float progressInterval;
    
    virtual bool init();
    
    static Scene * createScene();
    
    CREATE_FUNC(PreloadLayer);
    
    void loadingComplete();//资源全部加载完成，切换到另一个游戏场景
    void progressUpdate();//更新游戏进度条    
    
   // void onExit();
};

#endif /* defined(__MikuRun__PreloadLayer__) */
