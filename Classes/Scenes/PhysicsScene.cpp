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


    this->drawNode = DrawNode::create();
    this->drawNode->setContentSize(size);
    this->drawNode->setColor(Color3B::WHITE);
    this->drawNode->setLineWidth(5);
    addChild(drawNode);
    colorBall = Ball::createWithFile("colorball.png");
    auto crateSprite = Sprite::create("crate.png");
    crateSprite->setPosition(Vec2(size.width / 4, size.height / 2));
    colorBall->setPosition(Vec2(size.width / 2, size.height / 2));


    auto edgeBody = PhysicsBody::createEdgeBox(Size(size.width - 10, size.height - 10), PHYSICSBODY_MATERIAL_DEFAULT);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(size.width / 2, size.height / 2));
    edgeNode->setPhysicsBody(edgeBody);

    circle = PhysicsBody::createCircle(colorBall->getContentSize().width / 2, PhysicsMaterial(.3, .5, .5));
    colorBall->setPhysicsBody(circle);
    auto crateBody = PhysicsBody::createBox(crateSprite->getContentSize());
    crateBody->setAngularVelocity(10);
    crateBody->setAngularVelocityLimit(5);
    crateBody->setAngularDamping(1);

    crateSprite->setPhysicsBody(crateBody);
    circle->setCollisionBitmask(2);
    circle->setContactTestBitmask(true);
    edgeBody->setCollisionBitmask(1);

    this->addChild(edgeNode);
    this->addChild(crateSprite);
    this->addChild(colorBall);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(PhysicsScene::onTouchUp, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(PhysicsScene::onTouchDown, this);
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

            for (int i = 0; i < vector.size(); i++) {
                vecArray[i] = vector.at(i);
                if (i != 0) {
                    drawNode->drawLine(vector.at(i - 1), vector.at(i), Color4F::BLUE);
                }
            }


            auto newBody = PhysicsBody::createEdgeChain(vecArray, (int) vector.size());
            Node *newGround = Node::create();
            newGround->setPhysicsBody(newBody);
            addChild(newGround);
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

bool PhysicsScene::onTouchUp(Touch *touch, Event *unusedEvent) {
    Size size = Director::getInstance()->getVisibleSize();
    Vec2 res = touch->getLocation();
    if(res.x > size.width/2){

        colorBall->getPhysicsBody()->setVelocity(Vec2(500,0));
    }else{
        colorBall->getPhysicsBody()->setVelocity(Vec2(-500,0));
    }




//    colorBall->getPhysicsBody()->setVelocity(Vec2(random(-500, 500),
//                                                  random(-500, 500)));

    CCLOG("touch");

    return true;
}


void PhysicsScene::onTouchDown(Touch *touch, Event *unusedEvent) {
    colorBall->setLeft(false);
    colorBall->setRight(false);
}

void PhysicsScene::update(float dt) {

    if (colorBall->getRight()) {
        CCLOG("RIGHT");
        colorBall->getPhysicsBody()->applyForce(Vec2(1000000, 0), Vec2(0.5, 0.5));
    }
    if (colorBall->getLeft()) {
        CCLOG("LEFT");
        colorBall->getPhysicsBody()->applyForce(Vec2(-1000000, 0), Vec2(0.5, 0.5));
    }
}


