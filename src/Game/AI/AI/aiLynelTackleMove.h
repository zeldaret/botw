#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class LynelTackleMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(LynelTackleMove, ksys::act::ai::Ai)
public:
    explicit LynelTackleMove(const InitArg& arg);
    ~LynelTackleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mThroughDist_s{};
    // static_param at offset 0x40
    const float* mCloseEndAngle_s{};
    // static_param at offset 0x48
    const float* mCloseEndDist_s{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::ai
