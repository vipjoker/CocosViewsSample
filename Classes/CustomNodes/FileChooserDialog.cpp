//
// Created by omak on 07.11.17.
//

#include "FileChooserDialog.h"
const std::string img_letter = "letter.png";

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

    ui::EditBox *box = ui::EditBox::create(Size(50,30),img_letter);
    addChild(box);

    box->setPosition(Vec2(250,20));
    listFolder("/home/omak/Downloads/");
    listView->addEventListener([this](Ref *ref, ui::ListView::EventType type){
        CCLOG("Listview touched ");
        if(type == ui::ListView::EventType::ON_SELECTED_ITEM_END) {
            int position = listView->getCurSelectedIndex();
            ui::Layout *item = dynamic_cast<ui::Layout *>(listView->getItem(position));
            //item->setBackGroundColor(Color3B::R, Color3B::BLUE);
            ui::Text *text = dynamic_cast<ui::Text *>(item->getChildByTag(888));
            CCLOG("Text = %s", text->getString().c_str());
            listFolder(text->getString());
        }

    });

    return true;
}

ui::Layout *FileChooserDialog::createItem(std::string name,Color3B color) {
    ui::Layout *layout = ui::Layout::create();
    layout->setContentSize({500,100});
    layout->setBackGroundColorType(BackGroundColorType::GRADIENT);
    layout->setBackGroundColor(color,Color3B(100,100,100));
    layout->setTouchEnabled(true);
    ui::Text *text = ui::Text::create();
    text->setString(name);
    text->setColor(Color3B::BLACK);
    text->setTag(888);
    text->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    text->setPosition(Vec2(10,50));
    text->setFontSize(20);
    layout->addChild(text);
    return layout;
}

void FileChooserDialog::listFolder(const std::string path) {
    FileUtils *fileUtils = FileUtils::getInstance();
    listView->removeAllItems();
    for(auto str : fileUtils->listFiles(path)){

//        if(fileUtils->isDirectoryExist(str)){
        if(str.at(str.size() -1) == '/') {
            listView->addChild(createItem(str,Color3B::YELLOW));
        }
//        else{
//            listView->addChild(createItem(str,Color3B::WHITE));
//        }
//        }
    }
}
