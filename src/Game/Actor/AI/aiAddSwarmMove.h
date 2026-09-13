#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddSwarmMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AddSwarmMove, ksys::act::ai::Ai)
public:
    explicit AddSwarmMove(const InitArg& arg);
    ~AddSwarmMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mIgnoreSensorTime_s{};
    // static_param at offset 0x40
    const float* mSubSpeed_s{};
    // static_param at offset 0x48
    const float* mSubAccRateMin_s{};
    // static_param at offset 0x50
    const float* mSubAccRateMax_s{};
    // static_param at offset 0x58
    const bool* mIsEndBySensor_s{};
    // static_param at offset 0x60
    sead::SafeString mAnimName_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
