#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MoveAroundTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MoveAroundTarget, ksys::act::ai::Ai)
public:
    explicit MoveAroundTarget(const InitArg& arg);
    ~MoveAroundTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mTurnTimeBase_s{};
    // static_param at offset 0x40
    const int* mTurnTimeRand_s{};
    // static_param at offset 0x48
    const float* mStartRange_s{};
    // static_param at offset 0x50
    const float* mEndRange_s{};
    // static_param at offset 0x58
    const float* mChangeRangeRate_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
