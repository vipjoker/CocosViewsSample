//
// Created by oleh on 07.08.17.
//

#include "LetterNode.h"

bool LetterNode::init() {
    if(!Sprite::init()){
        return false;
    }

    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(LetterNode::onTouchDown,this);

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}



LetterNode *LetterNode::createWithFileAndName(const std::string &fileName, std::string *_letterName) {

    LetterNode *sprite = new (std::nothrow) LetterNode();
    if (sprite && sprite->initWithFile(fileName))
    {
        sprite->autorelease();
        sprite->letterName = _letterName;
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

bool LetterNode::onTouchDown(Touch *touch, Event *event) {
    log("touched ");
    return true;
}

LetterNode::LetterNode() {

}

LetterNode::~LetterNode() {

}
