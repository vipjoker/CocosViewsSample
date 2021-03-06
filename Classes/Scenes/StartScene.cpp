//
// Created by oleh on 03.08.17.
//


#include <cocos/ui/UIButton.h>
#include <cocos/ui/UIDeprecated.h>
#include "StartScene.h"
#include "CustomNodes/UiNode.h"
#include "EditorScene.h"
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
    Director::getInstance()->setClearColor(Color4F(95/255.0,187/255.0,210/255.0,1));

    LayerColor *color = LayerColor::create(Color4B::ORANGE);
    addChild(color);
    this->setupButton();

    Size size = Director::getInstance()->getVisibleSize();
    auto editorButton = Button::create("menu_item.png");
    editorButton->setScale9Enabled(true);
    editorButton->setTitleText("Editor");

    editorButton->setTitleColor(Color3B::BLACK);
    editorButton->setTitleFontSize(20);
    editorButton->setContentSize(Size(150,50));
    editorButton->setPosition(Vec2(size.width/2,200));
    addChild(editorButton);

    editorButton->addClickEventListener([](Ref *ref){
        Director::getInstance()->setClearColor(Color4F(21/255.0f,0/255.0f,71/255.0f,1));
        Director::getInstance()->replaceScene(EditorScene::createScene());
    });


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

        auto scene = TransitionZoomFlipX::create(0.3, MenuScene::createScene());

        Director::getInstance()->pushScene(scene);
    });

}

