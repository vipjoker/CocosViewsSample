//
// Created by oleh on 18.07.17.
//
#include "LetterNode.h"
#include "PhysicsScene.h"

bool PhysicsScene::init() {
    if (!Layer::init()) {
        return false;
    }


    Size size = Director::getInstance()->getVisibleSize();
    gameRoot = Node::create();

    drawNode = DrawNode::create();
    drawNode->setContentSize(size);
    drawNode->setColor(Color3B::WHITE);
    drawNode->setLineWidth(5);


    lastTouch = nullptr;
    colorBall = Ball::createWithFile("colorball.png");
    auto crateSprite = Sprite::create("crate.png");
    crateSprite->setPosition(Vec2(size.width / 4, size.height / 2));


    colorBall->setPosition(Vec2(size.width / 2, size.height / 2));


    auto edgeBody = PhysicsBody::createEdgeBox(Size(size.width * 3 - 10, size.height - 10),
                                               PHYSICSBODY_MATERIAL_DEFAULT);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(size.width / 2, size.height / 2));
    edgeNode->setPhysicsBody(edgeBody);

    circle = PhysicsBody::createCircle(colorBall->getContentSize().width / 2,
                                       PhysicsMaterial(.3, .5, .5));


    colorBall->setPhysicsBody(circle);
    auto crateBody = PhysicsBody::createBox(crateSprite->getContentSize());
    crateBody->setAngularVelocity(10);
    crateBody->setAngularVelocityLimit(5);
    crateBody->setAngularDamping(1);

    crateSprite->setPhysicsBody(crateBody);
    circle->setCollisionBitmask(2);
    circle->setContactTestBitmask(true);
    edgeBody->setCollisionBitmask(1);

    gameRoot->addChild(drawNode);
    gameRoot->addChild(edgeNode);
    gameRoot->addChild(crateSprite);
    gameRoot->addChild(colorBall);


    addChild(gameRoot);
    uiNode = UiNode::create();
    addChild(uiNode);
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PhysicsScene::touchDown, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PhysicsScene::touchUp, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(PhysicsScene::touchCanceled, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(PhysicsScene::touchMove, this);

    uiNode->getBtnBack()->addClickEventListener(CC_CALLBACK_1(PhysicsScene::onBackPressed, this));
    uiNode->getBtnSettings()->addClickEventListener(
            CC_CALLBACK_1(PhysicsScene::onSettingsPressed, this));


    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(PhysicsScene::onContactBegin, this);

//    sprite->runAction(Liquid::create(2, Size(32,24), 1, 20));
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    scheduleUpdate();
    tiles = TMXTiledMap::create("map2.tmx");

    TMXObjectGroup *group = tiles->getObjectGroup("physics");
    for (auto &obj : group->getObjects()) {
        ValueMap &dict = obj.asValueMap();
        std::string s = dict.at("name").asString();
        float x = dict.at("x").asFloat();
        float y = dict.at("y").asFloat();
        std::string type = dict.at("type").asString();
        if (type == "line") {
            log("line found");

            ValueVector &points = dict.at("polylinePoints").asValueVector();

            std::vector<Vec2> vector;
            for (auto p : points) {
                ValueMap &pMap = p.asValueMap();
                float px = pMap.at("x").asFloat();
                float py = pMap.at("y").asFloat();
                log("Points found x=%f y=%f", px, py);
                Vec2 current(px, size.height - py);
                vector.push_back(current);
            }
            Vec2 *vecArray = new Vec2[vector.size()];

            for (unsigned int i = 0; i < vector.size(); i++) {
                vecArray[i] = vector.at(i);
                if (i != 0) {
                    drawNode->drawLine(vector.at(i - 1), vector.at(i), Color4F::WHITE);
                }
            }


            auto newBody = PhysicsBody::createEdgeChain(vecArray, (int) vector.size());
            Node *newGround = Node::create();
            newGround->setPhysicsBody(newBody);
            gameRoot->addChild(newGround);
//            delete[] vector.data();
//            delete[] vecArray;

        }
        // ValueMap &points =  dict.at("polylinePoints").asValueMap();
        log("Value found name %s x %f y %f", s.c_str(), x, y);

    }


    return true;
}

Scene *PhysicsScene::createScene() {
    auto scene = Scene::createWithPhysics();
    auto layer = PhysicsScene::create();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
//    scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    layer->setPhysicsWorld(scene->getPhysicsWorld());
    scene->addChild(layer);
    return scene;
}

bool PhysicsScene::onContactBegin(PhysicsContact &contact) {
    auto a = contact.getShapeA()->getBody();
    auto b = contact.getShapeB()->getBody();

    if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 2) ||
        (b->getCollisionBitmask() == 1 && a->getCollisionBitmask() == 2)) {
        CCLOG("COLLISSION");
    }


    return true;
}


void PhysicsScene::onSettingsPressed(Ref *ref) {
    if (uiNode->getIsOpen()) {
        uiNode->closeDialog();
        getScene()->resume();
    } else {
        uiNode->openDialog();
        getScene()->pause();
    }

}

void PhysicsScene::onBackPressed(Ref *ref) {
    auto scene = StartScene::createScene();
    Director::getInstance()->replaceScene(scene);
}


bool PhysicsScene::touchDown(Touch *touch, Event *unusedEvent) {


    lastTime = clock();

    lastTouch = new Vec2(touch->getLocation() - gameRoot->getPosition());
    return true;
}


void PhysicsScene::touchMove(Touch *touch, Event *unusedEvent) {

    gameRoot->setPosition(touch->getLocation() - *lastTouch);


}


void PhysicsScene::touchUp(Touch *touch, Event *unusedEvent) {
    time_t timeSpend = (clock() - lastTime);
    float distance = touch->getLocation().distance(touch->getStartLocation());


    float speed = distance / timeSpend;
    log("Speed  is %f", speed);


    drawNode->drawSegment(touch->getStartLocation(), touch->getLocation(), 15, Color4F::RED);

    Vec2 loc = touch->getLocation() - touch->getStartLocation();

    loc.scale(speed * 10);
    gameRoot->stopAllActions();
    gameRoot->runAction(MoveBy::create(.5, loc));
    delete lastTouch;
    lastTouch = nullptr;

}

void PhysicsScene::touchCanceled(Touch *touch, Event *unusedEvent) {
    delete lastTouch;
    lastTouch = nullptr;
}

void PhysicsScene::update(float dt) {

    if (colorBall->getRight()) {
        CCLOG("RIGHT");
        colorBall->getPhysicsBody()->applyForce(Vec2(1000000, 0),
                                                colorBall->getPhysicsBody()->getPosition());
    }
    if (colorBall->getLeft()) {
        CCLOG("LEFT");
        colorBall->getPhysicsBody()->applyForce(Vec2(-1000000, 0),
                                                colorBall->getPhysicsBody()->getPosition());
    }
}





