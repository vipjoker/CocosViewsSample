//
// Created by oleh on 04.08.17.
//

#include "CustomMenuButton.h"

bool CustomMenuButton::init() {
    if(!Node::init()){
        return false;
    }
    label = Label::createWithTTF("Hello","fonts/Marker.ttf",30);
    label->setColor(Color3B::WHITE);
    label->setPosition(0, 100);
    this->setContentSize(Size(300, 300));
    log("Node dimmension init %f x %f", this->getContentSize().width, this->getContentSize().height);
    drawNode = DrawNode::create();
    drawNode->setAnchorPoint(Vec2(.5, .5));
    drawNode->drawSolidRect(Vec2(-50,0), Vec2(50,50),Color4F::RED);
    auto sprite = Sprite::create("HelloWorld.png");
    this->addChild(sprite);
    this->addChild(drawNode);
    this->addChild(label);

    return true;
}

void CustomMenuButton::onEnter() {
    Node::onEnter();
    log("Node dimmension onload %f x %f", this->getContentSize().width, this->getContentSize().height);
}
