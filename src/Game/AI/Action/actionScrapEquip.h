#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ScrapEquip : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(ScrapEquip, ActionWithAS)
public:
    explicit ScrapEquip(const InitArg& arg);
    ~ScrapEquip() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mWeaponIdx_s{};
    // static_param at offset 0x38
    const float* mDropSpd_s{};
};

}  // namespace uking::action
