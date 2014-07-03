//
//  Coin.cpp
//  MikuRun
//
//  Created by the9 on 14-6-24.
//
//

#include "Coin.h"
#include "GameScene.h"
Coin * Coin::createCoin()
{
    Coin *coin = new Coin();
    if (coin && coin->init()) {
        coin->autorelease();
        return coin;
    }
    CC_SAFE_DELETE(coin);
    return NULL;
}

bool Coin::init()
{

    Size size = Director::getInstance()->getWinSize();
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("coin.plist");
    this->initWithSpriteFrameName("coin1.png");

    
    Vector<SpriteFrame *> animFramesArray;
    for (int i=1; i<6+1; i++) {
        char name[64];
        sprintf(name, "coin%d.png", i);
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        animFramesArray.pushBack(frame);
    }
    Animation *animation = Animation::createWithSpriteFrames(animFramesArray,0.1);
    Animate *animateAction = Animate::create(animation);
    RepeatForever *repeatForever = RepeatForever::create(animateAction);
    this->runAction(repeatForever);
    
    return true;
}

void Coin::runAnimateAndStopFrame(int startframe,int stopframe)
{
    Vector<SpriteFrame *> animFramesArray;
    for (int i=startframe; i<stopframe+1; i++) {
    char name[64];
    sprintf(name, "coin%d.png", i);
    SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
    animFramesArray.pushBack(frame);
   
    }
    Animation *animation = Animation::createWithSpriteFrames(animFramesArray,0.1);
    Animate *animateAction = Animate::create(animation);
    RepeatForever *repeatForever = RepeatForever::create(animateAction);
    this->runAction(repeatForever);
}