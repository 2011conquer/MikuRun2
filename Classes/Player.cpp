//
//  Player.cpp
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#include "Player.h"
#include "GameFatherLayer.h"
#include "GameScene.h"

Player * Player::createPlayer( )
{
    Player *player = new Player();
    if (player && player->init()) {
        player->autorelease();
        player->initPlayer();
        return player;
    }
    CC_SAFE_DELETE(player);
    return NULL;
}

bool Player::initPlayer()
{
    Size size = Director::getInstance()->getWinSize();
    
    score = 0;
    runLength = 0.0f;
    
    SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
    frameCache->addSpriteFramesWithFile("run.plist");
    this->initWithSpriteFrameName("run1.png");
    
    Vector<SpriteFrame *> animFramesArray;
    for (int i=1; i<4; i++) {
        char name[64];
        sprintf(name, "run%d.png", i);
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        animFramesArray.pushBack(frame);
    }
    Animation *animation = Animation::createWithSpriteFrames(animFramesArray,0.1);
    Animate *animateAction = Animate::create(animation);
    RepeatForever *repeatForever = RepeatForever::create(animateAction);
    this->runAction(repeatForever);
    
    //初始化分数文字加入layer中
    Label *scoreLabel = Label::createWithSystemFont("分数：", "HelVetica-Blod", 24);
    scoreLabel->setPosition(size.width-150,size.height -20);
    GameScene::shareWorld()->addChild(scoreLabel);
    
    //分数数字加入到layer中
    string strScore = Convert2String(score);
    Label *scoreInLabel = Label::createWithSystemFont(strScore, "HelVetica-Blod", 24);
    scoreInLabel->setPosition(Point(size.width - 100, size.height - 20));
    scoreInLabel->setColor(Color3B(255, 255, 0));
    GameScene::shareWorld()->addChild(scoreInLabel,10,11);//tag值为11
    
    
    //跑动距离
    Label *lengthLabel = Label::createWithSystemFont("距离：", "HelVetica-Blod", 24);
    lengthLabel->setPosition(size.width-150,size.height -50);
    GameScene::shareWorld()->addChild(lengthLabel);
    
    //跑动距离数字加入到layer中
    string strLengthCount = Convert2String(runLength);
    strLengthCount +="/300";//用于显示成00/1000的格式
    Label *lengthInLabel = Label::createWithSystemFont(strLengthCount.c_str(), "HelVetica-Blod", 24);
    //c_str()函数返回一个指向正规C字符串的指针, 内容与本string串相同.
    // 这是为了与c语言兼容，在c语言中没有string类型，故必须通过string类对象的成员函数c_str()把string 对象转换成c中的字符串样式。
    lengthInLabel->setPosition(Point(size.width - 80, size.height - 50));
    lengthInLabel->setColor(Color3B(255,255,0));
    GameScene::shareWorld()->addChild(lengthInLabel,10,12);//tag值为11
    
    this->scheduleUpdate();//调用逐帧事件，计算跑动距离
    
    return true;
}


void Player::addScore(float _value)
{
    score += _value;//累加分数
    string strScore = Convert2String(score);//记得转换成字符串
    Label *ttf = (Label *)GameScene::shareWorld()->getChildByTag(11);//获取到label
    ttf->setString(strScore);

    if (runLength>=300) {
        //赢得游戏的情况下存储新的最高分
         int oldScore = atoi(UserDefault::getInstance()->getStringForKey("user_score","0").c_str());
        if (score>=oldScore) //通过时判断是否产生新纪录，并保存新的最高分
        {
            UserDefault::getInstance()->setStringForKey("user_score", Convert2String(score));
            UserDefault::getInstance()->flush();
        }
    }
}

void Player::addLength(float _value)
{
    runLength += _value;
    string strLength = Convert2String(runLength);
    strLength +="/300";
    Label *ttf = (Label *)GameScene::shareWorld()->getChildByTag(12);
    ttf->setString(strLength);
    
    if (isDead) {
        //当player挂掉以后存储最长距离
        int oldLength = atoi(UserDefault::getInstance()->getStringForKey("user_length","0").c_str());
        if (runLength>oldLength) {
            UserDefault::getInstance()->setStringForKey("user_length", Convert2String(runLength));
            UserDefault::getInstance()->flush();
        }
    }

    if (runLength>300) {
        //调用胜利界面
        GameScene::shareWorld()->winGame();
        this->unscheduleUpdate();
    }
}

void Player::update(float dt)
{
    count++;
    if (count>=10) {
        this->addLength(1);
        count = 0;
    }
    Point position =  GameScene::shareWorld()->getPlayer()->getPosition();
    //角色超出屏幕，游戏结束
    if (position.x<-this->getContentSize().width || position.y <-this->getContentSize().height) {
        isDead = true;
    }
    if (isDead) {
        GameScene::shareWorld()->lostGame();
         this->unscheduleUpdate();
    }
}

/*
Animate * Player::runAnimateAndStopFrame(int startframe,int stopframe)
{
    Vector<SpriteFrame *> animFramesArray;
    for (int i=startframe; i<stopframe; i++) {
        char name[64];
        sprintf(name, "run%d.png", i);
        SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        animFramesArray.pushBack(frame);
    }
    Animation *animation = Animation::createWithSpriteFrames(animFramesArray,0.1);
    Animate *animateAction = Animate::create(animation);
    return animateAction;
}
*/
