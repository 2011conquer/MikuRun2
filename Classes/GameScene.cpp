//
//  GameScene.cpp
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#include "GameScene.h"
#include "GameFatherLayer.h"
#include "SimpleAudioEngine.h"
#include "PauseLayer.h"
#include "GameWin.h"
#include "GameLost.h"


using namespace CocosDenshion;

static GameScene * gameScene = NULL;

Scene *GameScene::scene()
{
    Scene *scene = Scene::create();
    GameScene *layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init()) {
        return false;
    }
    gameScene = this;//用于获取游戏场景对象
    winSize = Director::getInstance()->getWinSize();
    
    floorCount = 16;//设置地面和金币的个数
    
    forceX = 300;
    forceY = 30;
    
    xSpeed = 5;
    ySpeed = 15;//决定跳的高度
    
    constXspeed = xSpeed;
    constYspeed = ySpeed;
    
    scaleFix = winSize.width/480;
    speedFix = 0.01;
    
    accelerate = 0.94;//加速度
    sizep =   Director::getInstance()->getWinSizeInPixels();
    scaleFix = sizep.width/480;
    
    isJump = false;
    isPlaySound=GameFatherLayer::allowSound();//是否播放音效
    isCollistionWithFloor =false;
    
    //创建背景地图
    BackMap *sky = BackMap::createMap("back_1.png");
    this->addChild(sky,0,0);
    BackMap *backMap = BackMap::createMap("back_5.png");
    this->addChild(backMap,0,1);
    
    //创建主角精灵
    player = Player::createPlayer();
    SpriteBatchNode *batchNode = SpriteBatchNode::create("run.png");
    batchNode->addChild(player, 2, 10);
    
    playerWidth = player->getContentSize().width;
    playerHeight = player->getContentSize().height;
    
    this->addChild(batchNode);
    
    player->setPosition(Point(-20, winSize.height/2 -100));
    
    MoveBy *move = MoveBy::create(1, Point(80, 0));
    player->runAction(move);
    
    Floor *temp = Floor::createFloor();
    floorWidth = temp->getContentSize().width;
    floorHeight = temp->getContentSize().height;
   
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("background.caf");
    SimpleAudioEngine::getInstance()->preloadEffect("eatcoin.caf");
    if (isPlaySound) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("background.caf");
    }
    
    //进度条
    coinNeededNum = 30;
    coinUsed = 0;
    isBarFull = false;
    progressInterval = 100.0/(float)coinNeededNum;
    Sprite *barSprite = Sprite::create("powerbar.png");
    progress = ProgressTimer::create(barSprite);
    progress->setPercentage(0.0f);
    progress->setMidpoint(Point(0, 0));
    progress->setBarChangeRate(Point(1, 0));
    progress->setScaleY(1.2);
    progress->setType(kCCProgressTimerTypeBar);
    progress->setAnchorPoint(Point(0, 0.5));
    progress->setPosition(Point(20, winSize.height-18));
    Sprite *proFrame = Sprite::create("powerui.png");
    proFrame->setAnchorPoint(Point(0, 0.3));
    progress->addChild(proFrame);
    this->addChild(progress);
    
    
    //添加返回主页按钮
    MenuItemImage *menuItem = MenuItemImage::create("btnmenu.png", "btnmenu.png",CC_CALLBACK_1(GameScene::menuButton, this));
    menuItem->setAnchorPoint(Point(1, 1));
    Menu *menu = Menu::create(menuItem, NULL);
    menu->setPosition(Point(winSize.width-20, winSize.height - 20));
    this->addChild(menu);
    
    this->initFloorsAndCoins();

    this->scheduleUpdate();
    
    return true;
}


void GameScene::progressUpdate()//更新游戏进度条
{
    if (--coinNeededNum) {
        progress->setPercentage(100.0f-progressInterval * coinNeededNum);
    }else{
        ProgressFromTo *ac = ProgressFromTo::create(1.5, progress->getPercentage(), 100);
        progress->runAction(ac);
        isBarFull = true;
      
    }
}

#pragma mark --逐帧调用方法--

void GameScene::update(float time)
{
    this->updateFloorsAndCoins();//逐帧改变金币和地面的位置
    this->isCollisionWithCoin();//与金币的碰撞检测
    this->jumpDownLogic();//逐帧调用，根据当前碰撞检测的结果决定要不要下落
    if (isBarFull) {
        for (int i=0; i<coinArray.size(); i++) {
            MoveTo *moveto = MoveTo::create(1.5, player->getPosition());
            DelayTime *delay = DelayTime::create(1.0);
            Sequence *sequ = Sequence::create(delay,moveto,NULL);
            coinArray.at(i)->runAction(sequ);
        }
        isBarFull = false;
        coinNeededNum = 30;
        progress->removeAllChildren();
        progress->setPercentage(0.0f);
        progress->setBarChangeRate(Point(1, 0));
        progress->setMidpoint(Point(0, 0));
        progress->setBarChangeRate(Point(1, 0));
        Sprite *proFrame = Sprite::create("powerui.png");
        proFrame->setAnchorPoint(Point(0, 0.3));
        progress->addChild(proFrame);
    }
}

void  GameScene::eventListenter()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->setEnabled(true);
    listener->onTouchBegan = [=](Touch *touch,Event *event){
        ySpeed = 15;
        ySpeed -=accelerate;
        
        jumpNum++;
        
        player->setPosition(player->getPosition()+ Point(0, ySpeed));
        
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

#pragma mark  --角色运动逻辑--

//逐帧调用下落方法
void GameScene::jumpDownLogic()
{
    isColliWithSide = false;
    ySpeed -= accelerate;
    //不需要遍历所有的地面，只遍历前几个就可以
    for (int i=0; i<4; i++) {
        Rect box =  floorArray.at(i)->boundingBox();
        //如果下落过程中发生碰撞，此处的判断语句已经确定碰撞到侧面
        if ((player->boundingBox().intersectsRect(box)
            //&& (player->getPositionX() + playerWidth/2)<= floorArray.at(i)->getPositionX() - floorWidth/2
            && abs((player->getPositionY() - floorArray.at(i)->getPositionY())) < (playerHeight/2+floorHeight/2-30))
            )
        {
            isColliWithSide = true;//碰撞到侧面
        }
        
        //判断是否踩到地面上
        if(player->boundingBox().intersectsRect(box)  &&
           abs(player->getPositionX() - floorArray.at(i)->getPositionX())<(playerWidth/2 + floorWidth/2-10) &&
           abs(player->getPositionY() - floorArray.at(i)->getPositionY()) <= (playerHeight/2 + floorHeight/2)
           )
        {
            isCollistionWithFloor = true;
            collNum = i;//获取到当前碰撞的地面
            ySpeed = -4;//初始纵方向速度为原值，以便下次跳起时使用
            break;
        }else{
        if (i == 3) {//当遍历到最后一个也没发生碰撞则
            isCollistionWithFloor = false;
        }
    }
}
    if (isCollistionWithFloor) {
        
        if (isColliWithSide == false) {

             player->setPositionY(floorArray.at(collNum)->getPositionY() + playerHeight/2 + floorHeight/2);
        }else{
            player->setPosition(player->getPosition() + Point(-forceX * speedFix, 0));
        }
        
       // player->setPositionY(floorArray.at(collNum)->getPositionY() + playerHeight/2 + floorHeight/2);
        this->eventListenter();
        if (jumpNum == 1) {
            jumpNum =0;
            }
         }
        else{
            player->setPosition(player->getPosition()+Point(0, ySpeed));
            if (jumpNum >= 2) {
                jumpNum = 0;
                _eventDispatcher->removeAllEventListeners();
            }
        }
}

#pragma mark --碰撞检测--
bool GameScene::isCollisionWithCoin() //和金币的碰撞检测
{
    bool  aFlag = false;
    
    for (int i=0; i<coinArray.size(); i++) {
        Rect box =  coinArray.at(i)->boundingBox();
        if (player->boundingBox().intersectsRect(box))
        {
            //当金币可见的时候才放粒子效果和音效
            if ( coinArray.at(i)->isVisible() == true) {
            coinArray.at(i)->setVisible(false);
            //粒子效果
            ParticleSystemQuad *paritcle = ParticleSystemQuad::create("physic-con.plist");
            paritcle->setPosition(coinArray.at(i)->getPosition());
            paritcle->setAutoRemoveOnFinish(true);
            this->addChild(paritcle,8);
             
            this->progressUpdate();//调用进度条事件
                
            player->addScore(1);//加分

            if (isPlaySound) {
                SimpleAudioEngine::getInstance()->playEffect("eatcoin.caf");
                }
            } 
        }
    }
    return aFlag;
}


#pragma mark --地面和金币初始化和处理--
void GameScene::initFloorsAndCoins()
{
    int num = 0;//用来作为数组下标
    int count = 0;//用来控制山体的X坐标
    
    isFrontBlank = false;
    
    //创建20个山体和金币，放入数组中
    for (int i=0; i<floorCount; i++) {
        Floor *floor = Floor::createFloor();
        floor->setScale(scaleFix);
        this->addChild(floor);
        floorArray.pushBack(floor);
        
       Coin *coin = Coin::createCoin();
       this->addChild(coin);
       coinArray.pushBack(coin);
        
    }
    //循环遍历修改山体和金币的位置
    while (num<floorCount) {
        count++;
        if (num<floorCount/2) {
            //前10个山体和金币单独处理,count用来控制位置,根据player的初始化位置设置地面的位置
            floorArray.at(num)->setPosition(Point(count*35,winSize.height/2 -100));
            
            Floor *floortemp = floorArray.at(num);
            //金币放在山体上方一定距离
            coinArray.at(num)->setPosition(Point(count*35,floortemp->getPositionY()+80));
            num++;
        }else{
            //后10个山体和金币的处理
            randomNum = this->getRandomNumber(0, 2); //0~2的随机数
            if (randomNum == 0) {
                isFrontBlank = true;
                continue;
            }
            if (isFrontBlank) {
                //山体高度设置为100到320-220即100之间的随机数
                floorArray.at(num)->setPosition(Point(count*35, this->getRandomNumber(winSize.height/2 -100, 180)));
                //金币高度设置为山体以上30到100的高度
                float y = floorArray.at(num)->getPositionY() + this->getRandomNumber(50, 150);
                coinArray.at(num)->setPosition(Point(count*35, y));
                
                isFrontBlank = false;
            }else{
                //设置山体的高度为前一个山体的高度
                floorArray.at(num)->setPosition(Point(count*35, floorArray.at(num -1)->getPositionY()));
                
                //金币的高度为山体以上30到100的高度
                float y = floorArray.at(num)->getPositionY() + this->getRandomNumber(50, 150);
                coinArray.at(num)->setPosition(Point(count*35, y));
            }
            num++;
        }
    }
}

void GameScene::updateFloorsAndCoins()
{
    //改变山体的位置
    for (int i =0; i<floorArray.size(); i++) {
        Floor *floor = floorArray.at(i);
        //forceX=300,speedFix = 0.01
        floor->setPosition(Point(floor->getPositionX()-forceX * speedFix, floor->getPositionY()));
    }
    //改变金币的位置
    for (int i = 0; i<coinArray.size(); i++) {
        Coin *coin = coinArray.at(i);
        coin->setPosition(Point(coin->getPositionX()-forceX * speedFix, coin->getPositionY()));
    }
    
    //当第一个山体移出屏幕
    if (floorArray.at(0)->getPositionX() <-50) {
        int num = floorArray.size()-1;//数组中最后一个元素下标
        float posx = floorArray.at(num)->getPositionX();//获取最后一个山体的X坐标
        
        //将第一个山体再加入数组中，这样它就成为最后一个元素
        floorArray.pushBack(floorArray.at(0));
        
        //删除数组中第一个元素，这样就完成了第一个山体移动到数组中最后的位置
        floorArray.eraseObject(floorArray.at(0));
        
        coinArray.pushBack(coinArray.at(0));
        coinArray.eraseObject(coinArray.at(0));
        
        //获取0~2的随机数
        randomNum = this->getRandomNumber(0, 2);
        if (randomNum == 0) {
            isFrontBlank = true;
            randomNum = this->getRandomNumber(1, 4);
        }
        
        Coin *coin = coinArray.at(num);
        //数组中最后一个元素，即原来的第一个元素移动到最后位置，再获取最后一个
       
        coin->setVisible(true);
        if (isFrontBlank) {
            //posx为数组中倒数第二个元素的X坐标，高度为随机数100~150之间
            //设置新的最后一个元素的位置
            floorArray.at(num)->setPosition(Point(posx + randomNum*35 + 35, this->getRandomNumber(winSize.height/2 -100,170)));
            coinArray.at(num)->setPosition(Point(posx + randomNum*35 + 35, floorArray.at(num)->getPositionY() + this->getRandomNumber(50, 150)));
            isFrontBlank = false;
        }else{
            //X轴坐标后移，高度同前一个山体
            floorArray.at(num)->setPosition(Point(posx + 35 , floorArray.at(num - 1)->getPositionY()));
            coinArray.at(num)->setPosition(Point(posx +  35, floorArray.at(num)->getPositionY() + this->getRandomNumber(50, 150)));
        }
        randomNum = this ->getRandomNumber(0, 2);
        if (randomNum == 0) {
            coin->setVisible(false);
        }
    }
}

#pragma mark --获取 世界 主角 数组--
GameScene* GameScene::shareWorld()
{
    return gameScene;
}

Player *GameScene:: getPlayer()
{
    return player;
}

void GameScene::menuButton(cocos2d::Ref *ref)
{
    Director::getInstance()->pause();//暂停游戏
    PauseLayer *pauselayer = PauseLayer::create();
    this->addChild(pauselayer,10);
    
}

Vector<Coin *>GameScene::getArrayForCoins()
{
    return coinArray;
}

Vector<Floor *>GameScene::getArrayForFloors()
{
    return floorArray;
}

void GameScene::winGame()
{
    Director::getInstance()->pause();//暂停游戏
    GameWin *winlayer = GameWin::create();
    this->addChild(winlayer,13);
}


void GameScene::lostGame()
{
    Director::getInstance()->pause();//暂停游戏
    GameLost *lostlayer = GameLost::create();
    this->addChild(lostlayer,14);
}


void GameScene::backMenu(Ref *ref)
{
    
}

// void GameScene::onEnter()
//{
//    Layer::onEnter();
//    SimpleAudioEngine::getInstance()->playBackgroundMusic("mikumusic.caf");
//}

// void GameScene::onExit()
//{
//    Layer::onExit();
//}

void GameScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}

void GameScene::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}

//获取一个from 到 to 之间的随机数，如(3,10),则返回 3 + arc4random()%8
//获取到的值范围是 3 + (0~7) = 3~10
int  GameScene::getRandomNumber(int from,int to)
{
    return (int)(from + (arc4random() % (to - from + 1)));
}