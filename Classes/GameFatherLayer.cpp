//
//  GameFatherLayer.cpp
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#include "GameFatherLayer.h"
#include "PreloadLayer.h"
#include "GameScene.h"
#include "ScoreScene.h"
#include "AboutScene.h"

#include <SimpleAudioEngine.h>
using namespace CocosDenshion;
static bool isSound =true;
Scene *GameFatherLayer::scene()
{
    Scene *scene = Scene::create();
    GameFatherLayer *layer = GameFatherLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameFatherLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    this->initUI();
    
    
    return true;
}

void GameFatherLayer::initUI()
{
    Size size = Director::getInstance()->getWinSize();
    LayerColor *layerColor = LayerColor::create(Color4B(223, 253, 253, 255), size.width, size.height);
    this->addChild(layerColor);
    
    Label *label = Label::create("初音跑酷", "Marker Felt", 45);
    label->setColor(Color3B(0, 0, 0));
    label->setPosition(Point(120, size.height-50));
    this->addChild(label);
    
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("menumusic.caf");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("menumusic.caf");
    
    isSound = true;
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mikustart.plist");
    Sprite *mySprite = Sprite::createWithSpriteFrameName("mikustart1.png");
    mySprite->setPosition(Point(size.width - 150, size.height/2));
    SpriteBatchNode *batchNode = SpriteBatchNode::create("mikustart.png");
    batchNode->addChild(mySprite);
    this->addChild(batchNode);
    
    Vector<SpriteFrame *> animFramesArray;
   // CCArray *animFramesArray = CCArray::create();
    for (int i=1; i<4; i++) {
        char name[64];
        sprintf(name, "mikustart%d.png", i);
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        animFramesArray.pushBack(frame);
     //   log("%zd",animFramesArray.size());
    }
    Animation *animation = Animation::createWithSpriteFrames(animFramesArray,0.15);
    Animate *animateAction = Animate::create(animation);
    RepeatForever *repeatForever = RepeatForever::create(animateAction);
    mySprite->runAction(repeatForever);
    
    MenuItemImage *startItem = MenuItemImage::create("newgameA.png", "newgameB.png",CC_CALLBACK_1(GameFatherLayer::startGame, this));
    startItem->setScale(0.8);
    
    MenuItemImage *aboutItem = MenuItemImage::create("aboutA.png", "aboutB.png",CC_CALLBACK_1(GameFatherLayer::aboutGame, this));
    aboutItem->setScale(0.8);
    
    MenuItemImage *scoreItem = MenuItemImage::create("score.png", "score.png",CC_CALLBACK_1(GameFatherLayer::scoreGame, this));

    
    auto menu = Menu::create(startItem, aboutItem, scoreItem,NULL);
    menu->alignItemsVerticallyWithPadding(20);
   //menu->alignItemsHorizontallyWithPadding(50);
    menu->setPosition(Point(120,size.height/2));
    this->addChild(menu, 1);
    
    //声音按钮
    soundItem =MenuItemImage::create("sound-on-A.png", "sound-on-B.png",CC_CALLBACK_1(GameFatherLayer::soundSwitch, this));
    auto soundMenu = Menu::create(soundItem, NULL);
    soundMenu->setScale(0.5);
    soundMenu->setAnchorPoint(Point(0, 0));
    soundMenu->setPosition(Point(30, 30));
    this->addChild(soundMenu);
    
}

void GameFatherLayer::startGame(Ref *sender)
{
    TransitionFade *transition = TransitionFade::create(1.5, GameScene::scene(), Color3B(255, 255, 255));
    Director::getInstance()->replaceScene(transition);
}

void GameFatherLayer::aboutGame(cocos2d::Ref *sender)
{
    TransitionFade *transition = TransitionFade::create(1.0, AboutScene::scene(), Color3B(255, 255, 255));
    Director::getInstance()->replaceScene(transition);
}

void GameFatherLayer::scoreGame(cocos2d::Ref *sender)
{
    TransitionFade *transition = TransitionFade::create(1.0, ScoreScene::scene(), Color3B(255, 255, 255));
    Director::getInstance()->replaceScene(transition);
}

void GameFatherLayer::soundSwitch(cocos2d::Ref *sender)
{
    if (!isSound) {
        soundItem->setNormalImage( Sprite::create("sound-on-A.png"));
        soundItem->setDisabledImage(Sprite::create("sound-on-B.png"));
        SimpleAudioEngine::getInstance()->playBackgroundMusic("menumusic.caf",true);
        isSound = true;
    }else{
        soundItem->setNormalImage(CCSprite::create("sound-off-A.png"));
        soundItem->setDisabledImage(CCSprite::create("sound-off-B.png"));
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        isSound = false;
    }
}

bool GameFatherLayer::allowSound()
{
    return isSound;
}
