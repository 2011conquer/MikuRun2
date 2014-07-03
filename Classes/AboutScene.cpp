//
//  AboutScene.cpp
//  MikuRun
//
//  Created by the9 on 14-6-24.
//
//

#include "AboutScene.h"
#include "GameFatherLayer.h"
using namespace std;
Scene *AboutScene::scene()
{
    Scene *scene = Scene::create();
    AboutScene *layer = AboutScene::create();
    scene->addChild(layer);
    return scene;
}

bool AboutScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    //获取设备尺寸
    Size size = Director::getInstance()->getWinSize();
    
    //设置背景
    Sprite *sp = Sprite::create("back_1.png");
    sp->setPosition(Point(size.width * 0.5, size.height *0.5));
    this->addChild(sp);
    
    //将分数以Label添加到layer并显示出来
    Label *ttfScore = Label::createWithSystemFont("关于我们", "Helvetica", 50);
    ttfScore->setPosition(Point(size.width*0.5 , size.height*0.5+50));
    ttfScore->setColor(Color3B(255,0,0));
    this->addChild(ttfScore);
    
    //添加一个按钮用于返回Menu
    Label *ttback = Label::createWithSystemFont("返回主菜单", "Helvetica", 23);
    ttback->setColor(Color3B(255,255,0));
    MenuItemLabel *menuLabel = MenuItemLabel::create(ttback, CC_CALLBACK_1(AboutScene::backMenu, this));
    //  menuLabel->setPosition(Point(0, 200));
    Menu *menu = Menu::create(menuLabel, NULL);
    menu->setPosition(Point(size.width/2, size.height/2-30));
    this->addChild(menu);
    
    return true;
}

void AboutScene::backMenu(cocos2d::Ref *ref)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1.5, GameFatherLayer::scene()));
}