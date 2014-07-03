//
//  PreloadLayer.cpp
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#include "PreloadLayer.h"
#include "GameScene.h"
#include <SimpleAudioEngine.h>

using namespace CocosDenshion;

Scene * PreloadLayer::createScene()
{
    Scene *scene = Scene::create();
    PreloadLayer *layer = PreloadLayer::create();
    scene->addChild(layer);
    return scene;
}


bool PreloadLayer::init()
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
    
//    numLoaded = 0;
    sourceCount = 30;
    
    /*
    
     this->loadImage("coin.png");
     this->loadImage("floor1.png");
     this->loadImage("mikustart.png");
     this->loadImage("run.png");
     this->loadImage("btnjump.png");
    
     this->loadImage("btnsound.png");
     this->loadImage("gamebk1.png");
     this->loadImage("progressbar.png");
     this->loadImage("powerbar.png");
     this->loadImage("powerui.png");
    
     this->loadImage("shu.png");
     this->loadImage("score.png");
     this->loadImage("back.png");
     this->loadImage("backA.png");
     this->loadImage("backB.png");
    
     this->loadImage("newgameA.png");
     this->loadImage("newgameB.png");
    this->loadImage("aboutA.png");
    this->loadImage("aboutB.png");
    this->loadImage("sound-on-A.png");
    
    this->loadImage("sound-on-B.png");
    this->loadMusic("mikumusic.caf");
    this->loadSounds("eatcoin.caf");
    this->loadImage("back_1.png");
    this->loadImage("back_5.png");
    
     
     */

    for (int i=0; i<30; i++) {
        this->progressUpdate();
    }
    progressInterval = 100.0/(float)sourceCount;
    
    return true;
}

void PreloadLayer::progressUpdate()
{
    if (--sourceCount) {
        progress->setPercentage(100.0f-progressInterval * sourceCount);
        log("还要加载%d个",sourceCount);
    }else{
        log("加载完了");
        ProgressFromTo *ac = ProgressFromTo::create(1.5, progress->getPercentage(), 100);
        DelayTime *delay = DelayTime::create(1.5f);
        Sequence *action = Sequence::create(delay, ac,NULL);
        progress->runAction(ac);
       this->loadingComplete();
    }
}

void PreloadLayer::loadingComplete()
{
    
    TransitionFade *transition = TransitionFade::create(1.5, GameScene::scene(), Color3B(255, 255, 255));
    Director::getInstance()->replaceScene(transition);
   
}
/*
 void PreloadLayer::onExit()
{
    Layer::onExit();
    log("删除进度条");
    this->removeChild(progress);
}
*/