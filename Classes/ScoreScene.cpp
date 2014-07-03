//
//  ScoreScene.cpp
//  MikuRun
//
//  Created by the9 on 14-6-24.
//
//

#include "ScoreScene.h"
#include "GameFatherLayer.h"
using namespace std;
Scene *ScoreScene::scene()
{
    Scene *scene = Scene::create();
    ScoreScene *layer = ScoreScene::create();
    scene->addChild(layer);
    return scene;
}

bool ScoreScene::init()
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
    
    //添加一个文本(获取存储的积分)
    string scoreStr = "";
    //获取存储的积分
    string score = UserDefault::getInstance()->getStringForKey("user_score","0").c_str();
    
    //判断当前是否有最高分得记录
    if (atoi(score.c_str())!=0) {
        //如果有最高分的记录
        scoreStr+=score;//这里是字符串相加用来连接
    }else{
        scoreStr="0";
    }
    
    //将分数以Label添加到layer并显示出来
    Label *ttfScore = Label::createWithSystemFont(scoreStr.c_str(), "Helvetica", 23);
    ttfScore->setPosition(Point(size.width*0.5 -50, size.height*0.5+40));
    ttfScore->setColor(Color3B(255,0,0));
    this->addChild(ttfScore);
    
    //添加一个按钮用于返回Menu
    Label *ttback = Label::createWithSystemFont("返回主菜单", "Helvetica", 23);
    ttback->setColor(Color3B(255,255,0));
    MenuItemLabel *menuLabel = MenuItemLabel::create(ttback, CC_CALLBACK_1(ScoreScene::backMenu, this));
  //  menuLabel->setPosition(Point(0, 200));
    Menu *menu = Menu::create(menuLabel, NULL);
    menu->setPosition(Point(size.width/2, size.height/2-30));
    this->addChild(menu);
    
    return true;
}

void ScoreScene::backMenu(cocos2d::Ref *ref)
{
    Director::getInstance()->replaceScene(TransitionSlideInR::create(1.5, GameFatherLayer::scene()));
}