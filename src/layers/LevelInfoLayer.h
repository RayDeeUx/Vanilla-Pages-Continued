#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <raydeeux.pages_api/include/PageMenu.h>
#include "../Macros.h"

using namespace geode::prelude;

class $modify(PageLevelInfoLayer, LevelInfoLayer) {

    LATE_MODIFY(LevelInfoLayer::init);

    void setPages() {
        if (Mod::get()->getSettingValue<bool>("levelinfolayer-left-menu")) {
            if (auto leftSideMenu = getChildByID("left-side-menu")) {
                static_cast<PageMenu*>(leftSideMenu)->setPaged(4, PageOrientation::VERTICAL, 150);
            }
        }
    }

    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) {
            return false;
        }
        if (Mod::get()->getSettingValue<bool>("levelinfolayer-left-menu")) {
            if (auto leftSideMenu = getChildByID("left-side-menu")) {
                leftSideMenu->setPosition({leftSideMenu->getPosition().x, leftSideMenu->getPosition().y + 20});
            }
        }
        setPages();
        return true;
    }

    void levelDownloadFinished(GJGameLevel* p0) {
        LevelInfoLayer::levelDownloadFinished(p0);
        setPages();
    }
};