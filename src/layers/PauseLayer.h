#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <raydeeux.pages_api/PageMenu.h>
#include "../Macros.h"

using namespace geode::prelude;

class $modify(PagePauseLayer, PauseLayer) {

    LATE_MODIFY(PauseLayer::customSetup);

    void modifyMenu(CCNode* menu) {
        if (CCBool* dontModify = typeinfo_cast<CCBool*>(menu->getUserObject("dont-modify"_spr))) {
            if (dontModify->getValue()) {
                return;
            }
        }
        menu->ignoreAnchorPointForPosition(false);
        menu->setContentSize({450, 85});
    }

    void paginateMenu(CCNode* menu, int countPerPage, int maxHeight) {
        menu->setContentHeight(250);
        PageMenu* pageMenu = static_cast<PageMenu*>(menu);
        pageMenu->setPaged(countPerPage, PageOrientation::VERTICAL, maxHeight, 4);
        pageMenu->setFixed(30);
        pageMenu->setButtonScale(0.5f);
        menu->updateLayout();
    }

    void customSetup() {
        PauseLayer::customSetup();

        if (Mod::get()->getSettingValue<bool>("pause-layer-right-menu") && m_mainLayer) {
            if (auto rightMenu = m_mainLayer->getChildByID("right-button-menu")) {
                paginateMenu(rightMenu, 7, 230);
            }
        }
        if (Mod::get()->getSettingValue<bool>("pause-layer-left-menu")) {
            if (auto leftMenu = m_mainLayer->getChildByID("left-button-menu")) {
                paginateMenu(leftMenu, 8, 270);
            }
        }
        if (Mod::get()->getSettingValue<bool>("pause-layer-menu")) {
            if (auto centerMenu = getChildByIDRecursive("center-button-menu")) {
                modifyMenu(centerMenu);
                static_cast<PageMenu*>(centerMenu)->setPaged(6, PageOrientation::HORIZONTAL, 380);
            }
        }
    }
};
