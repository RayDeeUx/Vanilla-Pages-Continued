#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <raydeeux.pages_api/include/PageMenu.h>
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

    void paginateMenu(CCNode* menu, int countPerPage, int maxHeight, float padding = 4.f) {
        menu->setContentHeight(250);
        PageMenu* pageMenu = static_cast<PageMenu*>(menu);
        pageMenu->setPaged(countPerPage, PageOrientation::VERTICAL, maxHeight, padding);
        pageMenu->setFixed(30);
        pageMenu->setButtonScale(0.5f);
        menu->updateLayout();
    }

    void customSetup() {
        PauseLayer::customSetup();

        if (Mod::get()->getSettingValue<bool>("pause-layer-right-menu")) {
            if (auto rightMenu = getChildByID("right-button-menu")) {
                paginateMenu(rightMenu, GEODE_MOBILE(6) GEODE_DESKTOP(8), GEODE_MOBILE(130) GEODE_DESKTOP(190), GEODE_MOBILE(-4) GEODE_DESKTOP(-2));
                // rightMenu->setAnchorPointY(1.f);
                // rightMenu->setPositionY(290.f);
                GEODE_MOBILE(rightMenu->setScale(1.1f);)
            }
        }
        if (Mod::get()->getSettingValue<bool>("pause-layer-left-menu")) {
            if (auto leftMenu = getChildByID("left-button-menu")) {
                paginateMenu(leftMenu, 8, 275);
            }
        }
        if (Mod::get()->getSettingValue<bool>("pause-layer-menu")) {
            if (auto centerMenu = getChildByID("center-button-menu")) {
                modifyMenu(centerMenu);

                static_cast<PageMenu*>(centerMenu)->setPaged(6, PageOrientation::HORIZONTAL, 450);
            }
        }
    }
};
