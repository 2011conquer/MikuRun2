//
//  PauseLayer.cpp
//  MikuRun
//
//  Created by 程龙元 on 14-6-29.
//
//

#include "PauseLayer.h"
#include "GameFatherLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool PauseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size size = Director::getInstance()->getWinSize();
    
    MenuItemFont *backToGame = MenuItemFont::create("back", CC_CALLBACK_1(PauseLayer::backToGame, this));
    
    MenuItemFont *backToMenu = MenuItemFont::create("Menu", CC_CALLBACK_1(PauseLayer::backToMenu, this));
                                           
    auto menu = Menu::create(backToMenu,backToGame, NULL);
    menu->alignItemsHorizontallyWithPadding(50);
    menu->setPosition(Point(size.width/2, size.height/2));
    this->addChild(menu,100);
    
    return true;
}

void PauseLayer::backToGame(Ref *ref)
{
    this->removeChildByTag(100);
    this->removeFromParent();
    Director::getInstance()->resume();
}
void PauseLayer::backToMenu(Ref *ref)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(GameFatherLayer::scene());
}
