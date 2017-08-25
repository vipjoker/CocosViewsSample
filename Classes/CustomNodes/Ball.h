//
// Created by oleh on 25.08.17.
//

#ifndef MYGAME_BALL_H
#define MYGAME_BALL_H
#include "cocos2d.h"
USING_NS_CC;
class Ball :public Sprite{
    CC_SYNTHESIZE(bool,left,Left);
    CC_SYNTHESIZE(bool,right,Right);
    DrawNode *drawNode;
    void initOpt();
public:
    static Ball *createWithFile(const char *filename);


    Ball();
    ~Ball(){}

    void update(float dt);
};


#endif //MYGAME_BALL_H
