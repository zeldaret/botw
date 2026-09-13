#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Towing : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Towing, ksys::act::ai::Ai)
public:
    explicit Towing(const InitArg& arg);
    ~Towing() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // FIXME: remove this
    u8 pad_0x38[0x40];
    // static_param at offset 0x78
    const int* mKeepMaxTime_s{};
    // static_param at offset 0x80
    const int* mStopTowingDef_s{};
    // static_param at offset 0x88
    const float* mMaxSpeed_s{};
    // static_param at offset 0x90
    const float* mInitSpeed_s{};
    // static_param at offset 0x98
    const float* mAddSpeed_s{};
    // static_param at offset 0xa0
    const float* mStandardSpeed_s{};
    // static_param at offset 0xa8
    const float* mBrakeDecSpeed_s{};
    // static_param at offset 0xb0
    const float* mAttFrontRate_s{};
    // static_param at offset 0xb8
    const float* mSandCheckLength_s{};
    // static_param at offset 0xc0
    const float* mSandCheckAngle_s{};
};

}  // namespace uking::ai
