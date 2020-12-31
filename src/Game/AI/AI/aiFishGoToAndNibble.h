#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FishGoToAndNibble : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FishGoToAndNibble, ksys::act::ai::Ai)
public:
    explicit FishGoToAndNibble(const InitArg& arg);
    ~FishGoToAndNibble() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mNumTimeNibbleMin_s{};
    // static_param at offset 0x40
    const int* mNumTimeNibbleRand_s{};
    // static_param at offset 0x48
    const float* mDistStartNibble_s{};
    // static_param at offset 0x50
    const float* mDistBackward_s{};
    // static_param at offset 0x58
    const float* mDepthGiveUp_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x68
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
