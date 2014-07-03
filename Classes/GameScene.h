//
//  GameScene.h
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#ifndef __MikuRun__GameScene__
#define __MikuRun__GameScene__

#include <iostream>
#include "Headers.h"
#include "Floor.h"
#include "BackMap.h"
#include "Coin.h"
#include "Player.h"
#include "PowerBar.h"


//人物状态
enum ROLE_STATE {
    ROLE_INVAILD_STATE = 0,
    ROLE_RUN,
    ROLE_JUMP_UP,
    ROLE_JUMP_DOWN
};


typedef  enum COLL_STATE {
    isOriginal = 0,
    isOnFloor ,
    isJumpUp,
    isJumpDown
}playerState;

class GameScene:public Layer
{
private:
    Size winSize;//屏幕大小
    
    float playerRigthtX;//人物前边框的x坐标
    float playerBottomY;//人物下边框的y坐标
    
    float floorTopY;//地面上边框的y坐标
    float floorLeftX;//地面后边框的x坐标
    
    float floorHeight;//地面高度
    float floorWidth;//地面宽度
    
    float playerWidth;//人物宽度
    float playerHeight;//人物高度
    
    int collNum;//发生碰撞的数组元素下标
    
    int jumpNum;//用来记录跳跃次数
    
    bool isJump;//是否跳起
    bool isCollistionWithFloor;//是否与地面发生碰撞
    bool isColliWithSide;
    bool isPlaySound;
    bool isFrontBlank;
    float forceX;
    float speedFix;
    float forceY;
    float scaleFix;
    
    float accelerate;
    
    Size sizep;
    
    int randomNum;
    
    void jumpDownLogic();
    
    bool isCollisionWithCoin();
    
    Player *player;
    
public:
    
    CC_SYNTHESIZE(ROLE_STATE, currentRoleState, CurrentRoleState);
    
    //人物速度（暂时未使用）
    CC_SYNTHESIZE(float, xSpeed, XSpeed);
    CC_SYNTHESIZE(float, ySpeed, YSpeed);
    //用于保留人物速度状态，便于恢复
    CC_SYNTHESIZE(float, constXspeed, ConstXspeed);    
    CC_SYNTHESIZE(float, constYspeed, ConstYspeed);
    
    
    CREATE_FUNC(GameScene);
    
    static Scene *scene();
    
    void eventListenter();
    
    void initFloorsAndCoins();
    
    void updateFloorsAndCoins();
    
    virtual bool init();

    static GameScene* shareWorld();
    
    //进度条
    ProgressTimer *progress;
    //代表进度条更新的次数
    float progressInterval;
    
    int coinNeededNum;
    int coinUsed;
    bool isBarFull;
    void progressUpdate();//更新游戏进度条
    
    void winGame();
    
    void lostGame();
    
    void backMenu(Ref *ref);
    
    void menuButton(Ref *ref);//菜单
    
    virtual void update(float time);
    
   Vector<Coin *> coinArray;
   Vector<Coin *>getArrayForCoins();
  
    int floorCount;
    Vector<Floor *> floorArray;
    Vector<Floor*>getArrayForFloors();
    
    int getRandomNumber(int from,int to);
    
    Player * getPlayer();
    
  // virtual void onEnter();

  //  virtual void onExit();

    void onEnterTransitionDidFinish();

    void onExitTransitionDidStart();
};

#endif /* defined(__MikuRun__GameScene__) */
