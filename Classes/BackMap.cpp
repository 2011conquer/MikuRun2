//
//  BackMap.cpp
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#include "BackMap.h"

BackMap *BackMap::createMap(const char *fileName)
{
    BackMap *map = new BackMap();
    if (map && map->init()) {
        map->mapInit(fileName);
        map->autorelease();
        return map;
    }
    
    CC_SAFE_DELETE(map);
    return NULL;
}

void BackMap::mapInit(const char *fileName)
{
    Size size = Director::getInstance()->getWinSize();
    //背景初始化
    
    Sprite* sky1 = Sprite::create(fileName);
    sky1->setPosition(Point(sky1->getContentSize().width*0.5, sky1->getContentSize().height*0.5));
    this->addChild(sky1,0,tag_oneImg);
    
    Sprite* sky2 = Sprite::create(fileName);
    sky2->setPosition(Point(sky1->getContentSize().width*1.5, sky1->getContentSize().height*0.5));
    this->addChild(sky2,0,tag_twoImg);

    this->scheduleUpdate();
}
void BackMap::update(float time)
{
    Size size = Director::getInstance()->getWinSize();
    Sprite *sp1 =(Sprite *)this->getChildByTag(tag_oneImg);
    //当第一张地图超出屏幕外，将其重置坐标，接在当前显示的图片后面
    if (sp1->getPositionX()<=-sp1->getContentSize().width/2) {
        sp1->setPosition(Point(sp1->getContentSize().width*1.5-2.5f, sp1->getContentSize().height/2));
    }else{
         sp1->setPosition(sp1->getPosition()+Point(-2, 0));
    }

    Sprite *sp2 =(Sprite *)this->getChildByTag(tag_twoImg);
    //当第二张地图超出屏幕外，将其重置坐标，接在当前显示的图片后面
    if (sp2->getPositionX()<=-sp2->getContentSize().width/2) {
        sp2->setPosition(Point(sp2->getContentSize().width*1.5-2.5f, sp2->getContentSize().height/2));
    }else{
        sp2->setPosition(sp2->getPosition()+Point(-2, 0));
    }  
}

void BackMap::onExit(){
   this->unscheduleUpdate();
   Layer::onExit();
}