#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EmitEffectLoopAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EmitEffectLoopAction, ksys::act::ai::Action)
public:
    explicit EmitEffectLoopAction(const InitArg& arg);
    ~EmitEffectLoopAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    float* mScale_d{};
    // dynamic_param at offset 0x28
    float* mX_d{};
    // dynamic_param at offset 0x30
    float* mY_d{};
    // dynamic_param at offset 0x38
    float* mZ_d{};
    // dynamic_param at offset 0x40
    float* mRX_d{};
    // dynamic_param at offset 0x48
    float* mRY_d{};
    // dynamic_param at offset 0x50
    float* mRZ_d{};
    // dynamic_param at offset 0x58
    float* mR_d{};
    // dynamic_param at offset 0x60
    float* mG_d{};
    // dynamic_param at offset 0x68
    float* mB_d{};
    // dynamic_param at offset 0x70
    float* mA_d{};
    // dynamic_param at offset 0x78
    bool* mOverWrite_d{};
    // dynamic_param at offset 0x80
    bool* mNoFade_d{};
    // dynamic_param at offset 0x88
    sead::SafeString mActor_d{};
    // dynamic_param at offset 0x98
    sead::SafeString mInstanceName_d{};
    // dynamic_param at offset 0xa8
    sead::SafeString mELinkKey_d{};
    // dynamic_param at offset 0xb8
    sead::SafeString mOption_d{};
    // dynamic_param at offset 0xc8
    bool* mCutChangeReset_d{};
};

}  // namespace uking::action
