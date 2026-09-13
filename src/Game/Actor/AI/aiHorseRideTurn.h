#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideTurn : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(HorseRideTurn, ksys::act::ai::Ai)
public:
    explicit HorseRideTurn(const InitArg& arg);
    ~HorseRideTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFinAngle_s{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
