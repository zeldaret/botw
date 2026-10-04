#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCRunaway : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCRunaway, ksys::act::ai::Ai)
public:
    explicit NPCRunaway(const InitArg& arg);
    ~NPCRunaway() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mReleaseDistance_s{};
    // static_param at offset 0x40
    const float* mCorneredDistance_s{};
    // static_param at offset 0x48
    const float* mStandRateTime_s{};
    // static_param at offset 0x50
    const float* mStandingTime_s{};
    // dynamic_param at offset 0x58
    int* mTerrorLevel_d{};
    // dynamic_param at offset 0x60
    int* mTerrorLayer_d{};
    // dynamic_param at offset 0x68
    bool* mIsReturnFromDemo_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetVel_d{};
};

}  // namespace uking::ai
