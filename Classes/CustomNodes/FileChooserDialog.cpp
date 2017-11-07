//
// Created by omak on 07.11.17.
//

#include "FileChooserDialog.h"

bool FileChooserDialog::init() {
    if(!ui::Layout::init()){
        return false;
    }

    ui::Button *btn = ui::Button::create("cross_icon/close_small.png");
    btn->setContentSize({25,25});
    btn->setAnchorPoint(Point::ANCHOR_MIDDLE);
    btn->setPosition({500,500});
    btn->addClickEventListener([this](Ref *ref){
        removeFromParentAndCleanup(true);
    });
    setAnchorPoint(Point::ANCHOR_MIDDLE);
    setContentSize({500,500});
    setBackGroundColorType(BackGroundColorType::SOLID);
    setBackGroundColor(Color3B::WHITE);
    setBackGroundColorOpacity(200);
    addChild(btn,2);

    listView = ui::ListView::create();
    listView->setContentSize({500,400});
    listView->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
    listView->setPosition(Vec2(250,500));
    listView->setBackGroundColorType(BackGroundColorType::SOLID);
    listView->setBackGroundColor(Color3B::BLUE);
    listView->setBackGroundColorOpacity(200);
    addChild(listView);
    listView->addChild(createItem("FIRST"));
    listView->addChild(createItem("Second"));
    listView->addChild(createItem("Third"));
    listView->addChild(createItem("Third"));
    listView->addChild(createItem("Third"));
    listView->addChild(createItem("Third"));
    listView->addChild(createItem("Third"));
    listView->addChild(createItem("Third"));
    listView->addChild(createItem("Third"));
    listView->addChild(createItem("Third"));



    return true;
}

ui::Layout *FileChooserDialog::createItem(std::string name) {
    ui::Layout *layout = ui::Layout::create();
    layout->setContentSize({500,100});
    layout->setBackGroundColorType(BackGroundColorType::GRADIENT);
    layout->setBackGroundColor(Color3B::WHITE,Color3B::BLACK);
    ui::Text *text = ui::Text::create();
    text->setString(name);
    text->setColor(Color3B::BLACK);
    text->setPosition(Vec2(10,10));
    layout->addChild(text);
    return layout;
}
