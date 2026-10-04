#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class BokoblinNoise : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BokoblinNoise, ksys::act::ai::Ai)
public:
    explicit BokoblinNoise(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mMaxContinueNum_s{};
    // static_param at offset 0x40
    const int* mEnterNoiseRate_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
