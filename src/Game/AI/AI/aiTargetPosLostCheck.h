#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPosLostCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TargetPosLostCheck, ksys::act::ai::Ai)
public:
    explicit TargetPosLostCheck(const InitArg& arg);
    ~TargetPosLostCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mLostTimer_s{};
    // static_param at offset 0x40
    const float* mLostVMin_s{};
    // static_param at offset 0x48
    const float* mLostVMax_s{};
    // static_param at offset 0x50
    const float* mLostRange_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
