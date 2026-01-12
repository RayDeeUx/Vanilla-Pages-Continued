#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include <alphalaneous.pages_api/include/PageMenu.h>
#include "../Macros.h"

using namespace geode::prelude;

class $modify(PageEditorPauseLayer, EditorPauseLayer) {

    LATE_MODIFY(EditorPauseLayer::init);

    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorPauseLayer::init(editorLayer)) {
            return false;
        }

        if (Mod::get()->getSettingValue<bool>("editor-pause-guidelines-menu")) {
            if (auto guidelinesMenu = this->getChildByID("guidelines-menu")) {
                guidelinesMenu->setLayout(RowLayout::create()->setAutoScale(true));
                static_cast<PageMenu*>(guidelinesMenu)->setPaged(6, PageOrientation::HORIZONTAL, (CCDirector::get()->getWinSize().width / 2) - 35, 2);
                static_cast<PageMenu*>(guidelinesMenu)->setButtonScale(.75f);
            }
        }

        return true;
    }

/*
    void createPageForTabs(std::string id) {
        if (auto tabsMenu = getChildByID(id.c_str())) {
            if (auto toolbarTogglesMenu = getChildByID("toolbar-toggles-menu")) {
                tabsMenu->setPositionY(toolbarTogglesMenu->getScaledContentSize().height);
                tabsMenu->setAnchorPoint({0.5, 0});
                CCSize winSize = CCDirector::get()->getWinSize();

                float scale = tabsMenu->getScale();

                float newWidth = 520 / scale;

                tabsMenu->setContentSize({newWidth, 17.5});

                PageMenu* pageMenu = static_cast<PageMenu*>(tabsMenu);

                pageMenu->setPaged(std::ceil(16 / scale), PageOrientation::HORIZONTAL, winSize.width);
                pageMenu->setButtonScale(0.5f);
            }
        }
    }
*/
};
