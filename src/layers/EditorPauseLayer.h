#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include <raydeeux.pages_api/PageMenu.h>
#include "../Macros.h"

using namespace geode::prelude;

class $modify(PageEditorPauseLayer, EditorPauseLayer) {
    LATE_MODIFY(EditorPauseLayer::init);

    bool init(LevelEditorLayer* editorLayer) {
        if (!EditorPauseLayer::init(editorLayer)) {
            return false;
        }

        if (Mod::get()->getSettingValue<bool>("editor-pause-settings-menu")) {
            if (auto settingsMenu = this->getChildByID("settings-menu")) {
                settingsMenu->setLayout(ColumnLayout::create()->setAutoScale(true)); // this is to compensate for anyone else thinking they're a comedian by copying nwo5's past war crime of disabling autoscale on node other mods rely on
                static_cast<PageMenu*>(settingsMenu)->setPaged(7, PageOrientation::VERTICAL, 250, -17.5);
            }
        }

        return true;
    }
};