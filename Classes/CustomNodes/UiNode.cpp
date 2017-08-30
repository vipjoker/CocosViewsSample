//
// Created by oleh on 04.08.17.
//

#include <Scenes/StartScene.h>
#include "UiNode.h"
#include "ui/CocosGUI.h"

using namespace ui;

bool UiNode::init() {
    if (!Node::init()) {
        return false;
    }

    colorLayer = LayerColor::create(Color4B(255, 0, 0, 128));
    setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    label = Label::createWithTTF("Hello", "fonts/Marker.ttf", 30);
    label->setColor(Color3B::WHITE);
    label->setPosition(0, 100);
    this->setContentSize(Size(300, 300));
    log("Node dimmension init %f x %f", this->getContentSize().width, this->getContentSize().height);


    drawNode = DrawNode::create();
    drawNode->setAnchorPoint(Vec2(.5, .5));
    drawNode->drawSolidRect(Vec2(-50, 0), Vec2(50, 50), Color4F::RED);


    auto sprite = Sprite::create("HelloWorld.png");
    colorLayer->setContentSize(Director::getInstance()->getVisibleSize());
    colorLayer->setVisible(false);

    setupButtons();
    this->addChild(sprite, 5);
    this->addChild(drawNode, 6);
    this->addChild(label, 7);
    this->addChild(colorLayer, 0);

    return true;
}

void UiNode::onEnter() {
    Node::onEnter();
    log("Node dimmension onload %f x %f", this->getContentSize().width,
        this->getContentSize().height);
}


void UiNode::setupButtons() {
    Size size = Director::getInstance()->getVisibleSize();

    Button *btnBack = Button::create("comic_src/Back.png");
    btnBack->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    btnBack->setPosition(Vec2(10.0, size.height - 10));
    btnBack->addClickEventListener(CC_CALLBACK_1(UiNode::onBackPressed, this));

    Button *btnSettings = Button::create("comic_src/Exec.png");
    btnSettings->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
    btnSettings->setPosition(Vec2(size.width -10,size.height -10));
    btnSettings->addClickEventListener(CC_CALLBACK_1(UiNode::onSettingsPressed, this));
    addChild(btnBack, 5);
    addChild(btnSettings, 5);

}

void UiNode::onSettingsPressed(Ref *ref) {
    colorLayer->setVisible(!colorLayer->isVisible());
}

void UiNode::onBackPressed(Ref *ref) {
    auto scene = StartScene::createScene();
    Director::getInstance()->replaceScene(scene);
}
