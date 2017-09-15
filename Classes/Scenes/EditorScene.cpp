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
    scroll->setLayoutType(ui::Layout::Type::HORIZONTAL);

    scroll->setContentSize({300, 100});
    scroll->setPropagateTouchEvents(true);
    scroll->setSwallowTouches(false);
    scroll->setDirection(ui::ListView::Direction::HORIZONTAL);
    drawNode = DrawNode::create();
//    drawNode->setContentSize(size);
    addChild(drawNode);


    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    scroll->pushBackCustomItem(ui::Button::create("crate.png"));
    addChild(scroll);

    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *touch, Event *event) {
        auto shape = new Shape();
        shape->setBegin(touch->getLocation());
        shapes.pushBack(shape);
        return true;
    };
    listener->onTouchMoved = [this](Touch *touch, Event *event) {
        drawNode->clear();
        CCLOG("DRAWN %d", shapes.size());

        Shape *shape = shapes.at(shapes.size() - 1);
        shape->setEnd(touch->getLocation());
        for (Shape *s:shapes)
            s->draw(*drawNode);
    };

    listener->onTouchEnded = [](Touch *touch, Event *event) {

    };

    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

Scene *EditorScene::createScene() {
    Scene *scene = Scene::createWithPhysics();
    scene->addChild(EditorScene::create());
    CCLOG("Create scene");

    return scene;
}

