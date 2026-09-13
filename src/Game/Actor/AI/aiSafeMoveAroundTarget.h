#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SafeMoveAroundTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SafeMoveAroundTarget, ksys::act::ai::Ai)
public:
    explicit SafeMoveAroundTarget(const InitArg& arg);
    ~SafeMoveAroundTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mForceTurnTimeBase_s{};
    // static_param at offset 0x40
    const int* mForceTurnTimeRand_s{};
    // static_param at offset 0x48
    const int* mForceTurnStopTimeBase_s{};
    // static_param at offset 0x50
    const int* mForceTurnStopTimeRand_s{};
    // static_param at offset 0x58
    const int* mUpdateTargetPosTime_s{};
    // static_param at offset 0x60
    const int* mUpdateNumCalc_s{};
    // static_param at offset 0x68
    const float* mStartRange_s{};
    // static_param at offset 0x70
    const float* mEndRange_s{};
    // static_param at offset 0x78
    const float* mChangeRangeRate_s{};
    // static_param at offset 0x80
    const float* mTargetOffsetDegree_s{};
    // static_param at offset 0x88
    const float* mLOSFailOffsetDegree_s{};
    // static_param at offset 0x90
    const float* mMinOffsetLength_s{};
    // dynamic_param at offset 0x98
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
