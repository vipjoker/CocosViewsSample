//
// Created by oleh on 03.08.17.
//


#include <cocos/ui/UIButton.h>
#include <cocos/ui/UIDeprecated.h>
#include "StartScene.h"
#include "CustomNodes/CustomMenuButton.h"

#include "MenuScene.h"

using namespace ui;

Scene *StartScene::createScene() {
    Scene *scene = Scene::create();
    scene->addChild(StartScene::create());
    return scene;
}

bool StartScene::init() {
    if (!Layer::init()) {
        return false;
    }
    LayerColor *color = LayerColor::create(Color4B::ORANGE);
    addChild(color);
    this->setupButton();

    Size size = Director::getInstance()->getVisibleSize();


    return true;
}

void StartScene::setupButton() {
    Button *button = Button::create("button.png");

    button->setPositionType(Widget::PositionType::PERCENT);
    button->setContentSize(Size(200, 200));
    button->setPositionPercent(Vec2(.5, .5));

    auto scale =ScaleTo::create(0.5,0.8);
    auto scaleOut =ScaleTo::create(0.5,1);

    auto seq = Sequence::create(scale,scaleOut,NULL);
    auto repeatForewer = RepeatForever::create(EaseInOut::create(seq,1));

    button->runAction(repeatForewer);
    this->addChild(button);
    button->addClickEventListener([](Ref *ref) {

        auto scene = TransitionZoomFlipX::create(1, MenuScene::createScene());

        Director::getInstance()->pushScene(scene);
    });

}

