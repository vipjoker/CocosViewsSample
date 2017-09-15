//
// Created by omak on 15.09.17.
//

#ifndef MYGAME_SHAPE_H
#define MYGAME_SHAPE_H
#include "cocos2d.h"
#include "Editable.h"
USING_NS_CC;


class Shape :public Editable{
  //  Shape::Type type;
    CC_SYNTHESIZE(Vec2,begin,Begin);
    CC_SYNTHESIZE(Vec2,end,End);

public:
    Shape();
    ~Shape();
    void draw(DrawNode &drawNode);

    enum class Type{
        CIRCLE,SQUARE
    };
};


#endif //MYGAME_SHAPE_H
