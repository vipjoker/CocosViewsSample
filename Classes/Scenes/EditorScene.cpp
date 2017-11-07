//
// Created by omak on 07.09.17.
//


#include "external/sqlite3/include/sqlite3.h"
#include "EditorScene.h"
#include <vector>
#include "../CustomNodes/FileChooserDialog.h"

bool EditorScene::init() {
    if (!Layer::init()) {
        return false;
    }


    Size size = Director::getInstance()->getVisibleSize();
    auto scroll = ui::ListView::create();
    scroll->setLayoutType(ui::Layout::Type::HORIZONTAL);

    scroll->setContentSize({200, size.height});

    scroll->setPropagateTouchEvents(true);
    scroll->setSwallowTouches(false);
    scroll->setDirection(ui::ListView::Direction::VERTICAL);
    drawNode = DrawNode::create();
//    drawNode->setContentSize(size);
    addChild(drawNode);


  ui::Button *btn = ui::Button::create("menu_item.png");
    btn->setContentSize({100,30});
    btn->setScale9Enabled(true);
    btn->setTitleText("HELLO BUTTON");
    btn->setPosition(size/2);
    addChild(btn);
    btn->addClickEventListener([this](Ref *ref){
        Size s = Director::getInstance()->getVisibleSize();
        auto dilaog = FileChooserDialog::create();
        dilaog->setPosition(s/2);

        addChild(dilaog,5);
        CCLOG("Button clicked");
    });


    sqlite3 *pdb=NULL;
    std::string path=FileUtils::getInstance()->getDefaultResourceRootPath() +"save.db3";


    std::string sql;
    int result;
    result=sqlite3_open(path.c_str(),&pdb);
    if(result!=SQLITE_OK)
        CCLOG("open database failed,  number%d",result);





    for (int i = 0; i < 30; i++) {

        auto layerColor = ui::Layout::create();
        layerColor->setTouchEnabled(true);
        layerColor->setContentSize({200, 100});
        layerColor->setBackGroundColor(Color3B(random(150,200),random(150,200),random(150,200)));
        layerColor->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
        std::stringstream ss;
        ss <<  "Item " << i;

        auto text = ui::Text::create(ss.str(), "fonts/Monaco_Linux.ttf", 30);
        layerColor->addChild(text);
        text->setAnchorPoint(Point::ANCHOR_MIDDLE);
        text->setPosition({100, 50});


        scroll->pushBackCustomItem(layerColor);

    }
    scroll->addEventListener([](Ref *ref ,ui::ListView::EventType event){
        ui::ListView *listView = dynamic_cast<ui::ListView*>(ref);
        int index= listView->getCurSelectedIndex();
        CCLOG("Item pressed %d",index);

    });
    addChild(scroll);



    auto layout = ui::VBox::create();
    layout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
    layout->setBackGroundColor(Color3B::BLACK);
    layout->setContentSize({150,size.height});

    layout->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
    layout->setPosition({size.width,0});

    for(int i = 0; i < 10; i++){
        auto text = ui::Text::create("Text","fonts/Monaco_Linux.ttf", 30);
        
        layout->addChild(text);
    }
    addChild(layout);




    for(int j = 0; j < size.height; j+=20){
        for(int i = 0 ; i < size.width; i+=20){
            EditRect rect;
            rect.isPressed = false;
            rect.rect = Rect(Vec2(i,j),Size(20,20));
            rects.push_back(rect);
        }
    }


    EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
    listener->
            onTouchBegan = [this](Touch *touch, Event *event) {
        for(EditRect &r:rects){

            if(r.rect.containsPoint(touch->getLocation())){

                r.isPressed = !r.isPressed;
            }
        }
        update(0);
        return true;
    };
    listener->
            onTouchMoved = [this](Touch *touch, Event *event) {


//        Shape *shape = shapes.at(shapes.size() - 1);
//        shape->setEnd(touch->getLocation());
//        for (Shape *s:shapes)
//            s->draw(*drawNode);
    };

    listener->
            onTouchEnded = [](Touch *touch, Event *event) {

    };

    getEventDispatcher()->

            addEventListenerWithSceneGraphPriority(listener,
                                                   this);
//    scheduleUpdate();
    return true;
}

Scene *EditorScene::createScene() {
    Scene *scene = Scene::createWithPhysics();
    scene->addChild(EditorScene::create());
    CCLOG("Create scene");

    return scene;
}

void EditorScene::update(float dt) {

    CCLOG("UPDATE");
    drawNode->clear();
    for(EditRect r:rects){
        Rect rect = r.rect;
        if(r.isPressed)drawNode->drawSolidRect(rect.origin,rect.origin + rect.size,Color4F::RED);
    }

}

