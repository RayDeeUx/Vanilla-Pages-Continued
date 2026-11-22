#pragma once

#include <Geode/modify/EditLevelLayer.hpp>
#include <Geode/modify/LevelBrowserLayer.hpp>
#include <raydeeux.pages_api/PageMenu.h>
#include "../Macros.h"

using namespace geode::prelude;

class $modify(PageLevelBrowserLayer, LevelBrowserLayer) {

    LATE_MODIFY(LevelBrowserLayer::init);

    bool init(GJSearchObject* gjso) {
        if (!LevelBrowserLayer::init(gjso)) {
            return false;
        }

        if (Mod::get()->getSettingValue<bool>("level-browser-bottom-left-menu") && gjso->m_searchType == SearchType::MyLevels) {
            if (auto blm = this->getChildByID("bottom-left-menu")) {
                if (auto fuckass = typeinfo_cast<AxisLayout*>(blm->getLayout())) {
                    blm->setLayout(ColumnLayout::create()->setGap(fuckass->getGap())->setAutoScale(true)->ignoreInvisibleChildren(true));
                }
                
                static_cast<PageMenu*>(blm)->setPaged(3, PageOrientation::VERTICAL, blm->getContentHeight() + 20);
                static_cast<PageMenu*>(blm)->setButtonScale(.75f);
            }
        }

        return true;
    }
};

class $modify(PageEditLevelLayer, EditLevelLayer) {

    LATE_MODIFY(EditLevelLayer::init);

    bool init(GJGameLevel* lvl) {
        if (!EditLevelLayer::init(lvl)) {
            return false;
        }

        if (Mod::get()->getSettingValue<bool>("edit-level-level-actions-menu")) {
            if (auto lam = this->getChildByID("level-actions-menu")) {
                if (auto fuckass = typeinfo_cast<AxisLayout*>(lam->getLayout())) {
                    lam->setLayout(ColumnLayout::create()->setGap(fuckass->getGap())->setAutoScale(true)->ignoreInvisibleChildren(true));
                }

                static_cast<PageMenu*>(lam)->setPaged(6, PageOrientation::VERTICAL, lam->getContentHeight() * .75f);
                static_cast<PageMenu*>(lam)->setButtonScale(.75f);
            }
        }

        return true;
    }
};