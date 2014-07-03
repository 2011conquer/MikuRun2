//
//  GameWin.cpp
//  MikuRun
//
//  Created by the9 on 14-6-24.
//
//

#include "GameWin.h"
#include "GameLost.h"
#include "GameFatherLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

bool GameWin::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Size size = Director::getInstance()->getWinSize();
    
    Label *winLabel = Label::createWithSystemFont("You Win", "Helvetica", 40);
    winLabel->setPosition(Point(size.width*0.5, size.height*0.5 +40));
    winLabel->setColor(Color3B(255,0,0));
    GameScene::shareWorld()->addChild(winLabel);
    
    MenuItemFont *backToGame = MenuItemFont::create("重来", CC_CALLBACK_1(GameWin::resetButton, this));
    
    MenuItemFont *backToMenu = MenuItemFont::create("菜单", CC_CALLBACK_1(GameWin::backMenu, this));
    
    auto menu = Menu::create(backToMenu,backToGame, NULL);
    menu->alignItemsHorizontallyWithPadding(50);
    menu->setPosition(Point(size.width/2, size.height/2));
    this->addChild(menu,99);
    
    return true;
}

void GameWin::resetButton(Ref *ref)
{
    this->removeChildByTag(99);
    this->removeFromParent();
    Director::getInstance()->replaceScene(GameScene::scene());
    Director::getInstance()->resume();
}
void GameWin::backMenu(Ref *ref)
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(GameFatherLayer::scene());
}
