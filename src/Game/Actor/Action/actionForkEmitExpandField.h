#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkEmitExpandField : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkEmitExpandField, ksys::act::ai::Action)
public:
    explicit ForkEmitExpandField(const InitArg& arg);
    ~ForkEmitExpandField() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mAttackPower_s{};
    // static_param at offset 0x28
    const int* mAttackIntensity_s{};
    // static_param at offset 0x30
    const int* mAttackType_s{};
    // static_param at offset 0x38
    const int* mCutGrassType_s{};
    // static_param at offset 0x40
    const int* mAtTarget_s{};
    // static_param at offset 0x48
    const float* mScale_s{};
    // static_param at offset 0x50
    const float* mActorPowerScale_s{};
    // static_param at offset 0x58
    const bool* mIsUseAtCollision_s{};
    // static_param at offset 0x60
    sead::SafeString mPartsKey_s{};
    // static_param at offset 0x70
    sead::SafeString mXLinkKey_s{};
    // static_param at offset 0x80
    sead::SafeString mAtDirType_s{};
};

}  // namespace uking::action
