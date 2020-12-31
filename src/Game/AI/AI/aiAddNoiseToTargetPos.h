#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddNoiseToTargetPos : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AddNoiseToTargetPos, ksys::act::ai::Ai)
public:
    explicit AddNoiseToTargetPos(const InitArg& arg);
    ~AddNoiseToTargetPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRandYMin_s{};
    // static_param at offset 0x40
    const float* mRandYMax_s{};
    // static_param at offset 0x48
    const float* mRandLeftMax_s{};
    // static_param at offset 0x50
    const float* mRandRightMax_s{};
    // static_param at offset 0x58
    const float* mRandDistMin_s{};
    // static_param at offset 0x60
    const float* mRandDistMax_s{};
    // static_param at offset 0x68
    const bool* mIsUpdateEveryFrame_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
