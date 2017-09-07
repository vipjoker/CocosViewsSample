//
// Created by omak on 07.09.17.
//

#include "EditorScene.h"

bool EditorScene::init() {
        if(!Layer::init()){
            return false;
        }
    setTouchEnabled(true);
    return true;
}

Scene *EditorScene::createScene() {
    Scene *scene = Scene::createWithPhysics();
    scene->addChild(EditorScene::create());
    CCLOG("Create scene");

    return scene;
}

bool EditorScene::onTouchBegan(Touch *touch, Event *unused_event) {
    CCLOG("TOUCH received");
    return true;
}

void EditorScene::onTouchMoved(Touch *touch, Event *unused_event) {
    Layer::onTouchMoved(touch, unused_event);
}

void EditorScene::onTouchEnded(Touch *touch, Event *unused_event) {
    Layer::onTouchEnded(touch, unused_event);
}
