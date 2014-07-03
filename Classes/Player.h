//
//  Player.h
//  MikuRun
//
//  Created by the9 on 14-6-23.
//
//

#ifndef __MikuRun__Player__
#define __MikuRun__Player__

#include <iostream>
#include "Headers.h"
using namespace std;

template <typename T>
string Convert2String(const T & value) {
    stringstream ss;
    ss<<value;
    return ss.str();
}


class Player:public Sprite {
public:
   
    Animate *animateRun;
    Animate *animateJump;
    Animate *animateDown;
    
    virtual bool initPlayer();
    
    static Player *createPlayer();
    
    void addScore(float _value);//加分数
    
    void addLength(float _value);//加跑动距离
    
    int score;
    int runLength;
    int count;
    void update(float dt);
    
    bool isDead;//是否死亡
    
    Animate * runAnimateAndStopFrame(int startframe,int stopframe);
    
    
};

#endif /* defined(__MikuRun__Player__) */
