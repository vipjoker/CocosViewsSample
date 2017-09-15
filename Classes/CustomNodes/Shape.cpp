//
// Created by omak on 15.09.17.
//

#include "Shape.h"

Shape::Shape() {
    CCLOG("Shape created");
//    this->type = type;
    this->autorelease();
}

Shape::~Shape() {
    CCLOG("Shape removed");
}

void Shape::draw(DrawNode &drawNode) {
    drawNode.drawSolidCircle(begin,begin.distance(end),360, 64, Color4F::RED);
    resize(begin, end);
}
