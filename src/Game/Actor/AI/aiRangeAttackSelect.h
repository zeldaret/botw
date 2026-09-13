#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RangeAttackSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RangeAttackSelect, ksys::act::ai::Ai)
public:
    explicit RangeAttackSelect(const InitArg& arg);
    ~RangeAttackSelect() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mRangeDist_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x50
    const bool* mIsIgnoreSmallHit_s{};
};

}  // namespace uking::ai
