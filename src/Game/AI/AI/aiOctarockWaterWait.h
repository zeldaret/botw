#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OctarockWaterWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(OctarockWaterWait, ksys::act::ai::Ai)
public:
    explicit OctarockWaterWait(const InitArg& arg);
    ~OctarockWaterWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mNoRiseTime_s{};
    // static_param at offset 0x40
    const int* mRiseDelayTimeMin_s{};
    // static_param at offset 0x48
    const int* mRiseDelayTimeMax_s{};
    // static_param at offset 0x50
    const int* mFinishFloatDelayTimeMin_s{};
    // static_param at offset 0x58
    const int* mFinishFloatDelayTimeMax_s{};
    // static_param at offset 0x60
    const float* mMinHeightFromWater_s{};
    // aitree_variable at offset 0x68
    void* mOctarockFormChangeUnit_a{};
};

}  // namespace uking::ai
