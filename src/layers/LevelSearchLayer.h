#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/LevelSearchLayer.hpp>
#include <raydeeux.pages_api/include/PageMenu.h>
#include "../Macros.h"

using namespace geode::prelude;

class $modify(PageLevelSearchLayer, LevelSearchLayer) {

    LATE_MODIFY(LevelSearchLayer::init);

    bool init(int type) {
        if (!LevelSearchLayer::init(type)) {
            return false;
        }
        if (Mod::get()->getSettingValue<bool>("levelsearchlayer-other-filter")) {
            if (auto otherFilterMenu = getChildByID("other-filter-menu")) {
                static_cast<PageMenu*>(otherFilterMenu)->setPaged(3, PageOrientation::VERTICAL, 0.f, 134.f);
                static_cast<PageMenu*>(otherFilterMenu)->setButtonScale(.75f);
            }
        }
        return true;
    }
};