//
// Created by oleh on 25.08.17.
//

#include "Ball.h"

Ball *Ball::createWithFile(const char *filename) {

    Ball* pSprite = new Ball();

    if (pSprite->initWithFile(filename))
    {
        pSprite->autorelease();

        pSprite->initOpt();


        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Ball::initOpt() {
    drawNode = DrawNode::create();
    drawNode->setLineWidth(5);
    addChild(drawNode);

    Size size = getContentSize();
    Vec2 origin(size.width/2,size.height/2);
    auto label = Label::createWithTTF("HELLO","fonts/Marker.ttf",20);
    label->setAnchorPoint(Point::ANCHOR_MIDDLE);
    label->setPosition(origin);
    addChild(label);
    scheduleUpdate();


    drawNode->drawLine(origin,origin + Vec2(100,0),Color4F::WHITE);
}

Ball::Ball() {
    left = false;
    right = false;
}

void Ball::update(float dt) {

}
