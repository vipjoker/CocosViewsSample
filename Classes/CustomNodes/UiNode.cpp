//
// Created by oleh on 04.08.17.
//

#include <Scenes/StartScene.h>
#include "UiNode.h"


template<typename T>
std::string to_string(T value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

bool UiNode::init() {
    if (!Node::init()) {
        return false;
    }

    dialogLayer = LayerColor::create(Color4B(0, 0, 0, 128));
    setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);

    this->setContentSize(Size(300, 300));
    dialogLayer->setContentSize(Director::getInstance()->getVisibleSize());
    dialogLayer->setOpacity(0);
    setIsOpen(false);

    setupButtons();

    addChild(dialogLayer, 0);

    return true;
}

void UiNode::onEnter() {
    Node::onEnter();
    log("Node dimmension onload %f x %f", this->getContentSize().width,
        this->getContentSize().height);
}


void UiNode::setupButtons() {
    Size size = Director::getInstance()->getVisibleSize();

    btnBack = Button::create("comic_src/Back.png");
    btnBack->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    btnBack->setPosition(Vec2(10.0, size.height - 10));

    btnSettings = Button::create("comic_src/Exec.png");
    btnSettings->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    btnSettings->setPosition(Vec2(size.width - 10, size.height - 10));
    addChild(btnBack, 5);
    addChild(btnSettings, 5);
    dialog = ui::Scale9Sprite::create("menu_item.png");
    dialog->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    dialog->setContentSize(Size(size.width * 0.8,size.width * 0.8 ));
    dialog->setPosition(Vec2(size.width / 2, size.height));


    auto image = Sprite::create("girl.jpg");

    image->setPosition(dialog->getContentSize()/2);
    auto drawNode= DrawNode::create(5);
    auto mask = ClippingNode::create(drawNode);
//    mask->setInverted(true);
    //mask->setPosition(dialog->getContentSize().width/2,dialog->getContentSize().height/2);
    drawNode->setContentSize(dialog->getContentSize());
    drawNode->drawSolidCircle(Vec2(0, 0), 50, 360, 32, Color4F::MAGENTA);
    mask->addChild(image);

    dialog->addChild(mask);
    dialogLayer->addChild(dialog);

}

void UiNode::openDialog() {
    CCLOG("dialog open");


    Size size = Director::getInstance()->getVisibleSize();
    setIsOpen(true);
    dialog->stopAllActions();
    auto moveAct = MoveTo::create(.3,Vec2(size.width/2,size.height/2 - dialog->getContentSize().height/2));
    dialog->runAction(EaseBackIn::create(moveAct));
}

void UiNode::closeDialog() {
    Size size = Director::getInstance()->getVisibleSize();
    CCLOG("dialog close");
    setIsOpen(false);
    dialog->stopAllActions();
    dialog->runAction(MoveTo::create(.3,Vec2(size.width/2,size.height)));
}

