//
//  BackMap.h
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#ifndef __MikuRun__BackMap__
#define __MikuRun__BackMap__

#include <iostream>
#include "Headers.h"

typedef enum {
    tag_oneImg,
    tag_twoImg
}tagMap;//枚举两张地图背景交替出现

class BackMap:public Layer {
private:
    
    void mapInit(const char *fileName);//初始化
    void update(float time);
    void onExit();//生命周期函数的退出
    
public:
    
    CREATE_FUNC(BackMap);
    
    //实例化函数
    static BackMap *createMap(const char *fileName);
};

#endif /* defined(__MikuRun__BackMap__) */
