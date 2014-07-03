//
//  PowerBar.cpp
//  MikuRun
//
//  Created by the9 on 14-6-24.
//
//

#include "PowerBar.h"
#include "GameScene.h"
#include <SimpleAudioEngine.h>

using namespace CocosDenshion;


bool PowerBar::init()
{
    if (!Layer::init()) {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    //创建一个进度条精灵
    Sprite *barSprite = Sprite::create("progressbar.png");
    progress = ProgressTimer::create(barSprite);
    progress->setPercentage(0.0f);
    progress->setScale(0.5f);
    progress->setMidpoint(Point(0, 0));
    progress->setBarChangeRate(Point(0.5, 0));
    progress->setType(kCCProgressTimerTypeBar);
    progress->setPosition(Point(size.width/2, size.height/2-50));
    this->addChild(progress);

    sourceCount = 30;
    
    for (int i=0; i<30; i++) {
        this->progressUpdate();
    }
    progressInterval = 100.0/(float)sourceCount;
    
    return true;
}

void PowerBar::progressUpdate()
{
    if (--sourceCount) {
        progress->setPercentage(100.0f-progressInterval * sourceCount);
    }else{
        ProgressFromTo *ac = ProgressFromTo::create(1.5, progress->getPercentage(), 100);
        DelayTime *delay = DelayTime::create(1.5f);
        Sequence *action = Sequence::create(delay, ac,NULL);
        progress->runAction(ac);
        this->loadingComplete();
    }
}

void PowerBar::loadingComplete()
{
    
}