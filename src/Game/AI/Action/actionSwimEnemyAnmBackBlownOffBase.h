#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwimEnemyAnmBackBlownOffBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SwimEnemyAnmBackBlownOffBase, ksys::act::ai::Action)
public:
    explicit SwimEnemyAnmBackBlownOffBase(const InitArg& arg);
    ~SwimEnemyAnmBackBlownOffBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeed_s{};
    // static_param at offset 0x28
    const float* mBlownHeight_s{};
    // static_param at offset 0x30
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x38
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x40
    const float* mInWaterDepth_s{};
    // static_param at offset 0x48
    const float* mFloatDepth_s{};
    // static_param at offset 0x50
    const bool* mUseKnockbackDir_s{};
    // static_param at offset 0x58
    sead::SafeString mAS_s{};
};

}  // namespace uking::action
