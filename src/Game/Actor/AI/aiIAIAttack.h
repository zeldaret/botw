#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class IAIAttack : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(IAIAttack, ksys::act::ai::Ai)
public:
    explicit IAIAttack(const InitArg& arg);
    ~IAIAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mOffsetLR_s{};
    // static_param at offset 0x48
    const float* mCloseDistLR_s{};
    // static_param at offset 0x50
    const float* mClsoeDistFB_s{};
    // static_param at offset 0x58
    const float* mTiredAngle_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x68
    const bool* mIsAbleSkipNear_s{};
};

}  // namespace uking::ai
