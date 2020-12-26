#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsWaterBulletAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainsWaterBulletAction, ksys::act::ai::Action)
public:
    explicit RemainsWaterBulletAction(const InitArg& arg);
    ~RemainsWaterBulletAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mSignASFrame_s{};
    // static_param at offset 0x28
    const float* mMaxRotSpd_s{};
    // static_param at offset 0x30
    const float* mMinRotSpd_s{};
    // static_param at offset 0x38
    const float* mEndTimer_s{};
    // static_param at offset 0x40
    const bool* mIgnroeWater_s{};
    // static_param at offset 0x48
    const bool* mIgnoreGravity_s{};
    // static_param at offset 0x50
    const bool* mUseParentRevDirRot_s{};
    // static_param at offset 0x58
    sead::SafeString mSignASName_s{};
};

}  // namespace uking::action
