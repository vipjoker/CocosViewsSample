//
// Created by omak on 15.09.17.
//

#include "Editable.h"

Editable::Editable() {
    CCLOG("Editabe created");
    drawNode = DrawNode::create(3);
    addChild(drawNode);

}

Editable::~Editable() {
    CCLOG("Editable removed");
}

void Editable::resize(const Vec2 begin, const Vec2 end) {
    drawNode->clear();
    drawNode->drawRect(begin,end,Color4F::GREEN);
}
