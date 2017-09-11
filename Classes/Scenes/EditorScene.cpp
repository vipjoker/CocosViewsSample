//
// Created by omak on 07.09.17.
//

#include "EditorScene.h"

bool EditorScene::init() {
    if (!Layer::init()) {
        return false;
    }

    Size size = Director::getInstance()->getVisibleSize();
    auto scroll = ui::ListView::create();


    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    addChild(scroll);
    return true;
}

Scene *EditorScene::createScene() {
    Scene *scene = Scene::createWithPhysics();
    scene->addChild(EditorScene::create());
    CCLOG("Create scene");

    return scene;
}

