//
// Created by omak on 07.11.17.
//

#ifndef MYGAME_FILECHOOSERDIALOG_H
#define MYGAME_FILECHOOSERDIALOG_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class FileChooserDialog :public ui::Layout {
    ui::ListView *listView;
public:
    bool init();
    CREATE_FUNC(FileChooserDialog);
    ui::Layout *createItem(std::string name,Color3B color);
    void listFolder(const std::string path);

};


#endif //MYGAME_FILECHOOSERDIALOG_H
