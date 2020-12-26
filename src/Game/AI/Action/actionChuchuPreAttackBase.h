#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChuchuPreAttackBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ChuchuPreAttackBase, ksys::act::ai::Action)
public:
    explicit ChuchuPreAttackBase(const InitArg& arg);
    ~ChuchuPreAttackBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mJumpNum_s{};
    // static_param at offset 0x28
    const float* mMoveBoneRotRatio_s{};
    // static_param at offset 0x30
    const float* mMoveBoneRotSpeedMin_s{};
    // static_param at offset 0x38
    const float* mTurnSpeed_s{};
    // static_param at offset 0x40
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x48
    const float* mJumpHeight_s{};
    // static_param at offset 0x50
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
