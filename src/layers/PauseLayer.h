#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <alphalaneous.pages_api/include/PageMenu.h>
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

    void paginateMenu(CCNode* menu) {
        menu->setContentHeight(250);
        PageMenu* pageMenu = static_cast<PageMenu*>(menu);
        pageMenu->setPaged(8, PageOrientation::VERTICAL, 250);
        pageMenu->setFixed(30);
        pageMenu->setButtonScale(0.5f);

        if (AxisLayout* layout = typeinfo_cast<AxisLayout*>(menu->getLayout())) {
            layout->setAxisAlignment(AxisAlignment::Center);
            layout->setAxisReverse(false);
            layout->setGrowCrossAxis(false);
            layout->setCrossAxisOverflow(false);
        }
        menu->updateLayout();
    }

    void customSetup() {
        PauseLayer::customSetup();

        if (Mod::get()->getSettingValue<bool>("pause-layer-right-menu")) {
            if (auto rightMenu = getChildByID("right-button-menu")) {
                paginateMenu(rightMenu);
            }
        }
        if (Mod::get()->getSettingValue<bool>("pause-layer-left-menu")) {
            if (auto leftMenu = getChildByID("left-button-menu")) {
                paginateMenu(leftMenu);
            }
        }
        if (Mod::get()->getSettingValue<bool>("pause-layer-menu")) {
            if (auto centerMenu = getChildByID("center-button-menu")) {
                modifyMenu(centerMenu);

                if (!centerMenu->getLayout()) {
                    Layout* layout = RowLayout::create();
                    RowLayout* rLayout = static_cast<RowLayout*>(layout);
                    rLayout->setGrowCrossAxis(true);
                    rLayout->setCrossAxisOverflow(false);
                    rLayout->setAxisAlignment(AxisAlignment::Center);
                    rLayout->setCrossAxisAlignment(AxisAlignment::Center);
                    rLayout->setCrossAxisLineAlignment(AxisAlignment::Center);
                    rLayout->setGap(10);
                    rLayout->ignoreInvisibleChildren(true);
                    centerMenu->setLayout(rLayout);
                }

                static_cast<PageMenu*>(centerMenu)->setPaged(6, PageOrientation::HORIZONTAL, 450);
            }
        }
    }
};