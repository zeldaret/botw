#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SandwormBlownOff : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SandwormBlownOff, ksys::act::ai::Action)
public:
    explicit SandwormBlownOff(const InitArg& arg);
    ~SandwormBlownOff() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mLimitDamage_s{};
    // static_param at offset 0x28
    const float* mSandOffsetSpeed_s{};
    // static_param at offset 0x30
    const float* mTargetSandOffset_s{};
    // static_param at offset 0x38
    const float* mTimer_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
    // static_param at offset 0x50
    sead::SafeString mDamageASName_s{};
    // static_param at offset 0x60
    sead::SafeString mSmallDamageASName_s{};
    // static_param at offset 0x70
    sead::SafeString mDamageRigidName_s{};
};

}  // namespace uking::action
