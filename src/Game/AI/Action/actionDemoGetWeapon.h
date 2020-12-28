#pragma once

#include "Game/AI/Action/actionDemoGetItem.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoGetWeapon : public DemoGetItem {
    SEAD_RTTI_OVERRIDE(DemoGetWeapon, DemoGetItem)
public:
    explicit DemoGetWeapon(const InitArg& arg);
    ~DemoGetWeapon() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
