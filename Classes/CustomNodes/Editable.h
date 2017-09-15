//
// Created by omak on 15.09.17.
//

#ifndef MYGAME_EDITABLE_H
#define MYGAME_EDITABLE_H
#include "cocos2d.h"
USING_NS_CC;

class Editable:public Node{
    DrawNode *drawNode;
protected:
    void resize(const Vec2 begin,const Vec2 end);
    Editable();
    ~Editable();
};


#endif //MYGAME_EDITABLE_H
