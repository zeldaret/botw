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
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
