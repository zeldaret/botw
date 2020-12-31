#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SwarmRangeKeepCircleMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SwarmRangeKeepCircleMove, ksys::act::ai::Ai)
public:
    explicit SwarmRangeKeepCircleMove(const InitArg& arg);
    ~SwarmRangeKeepCircleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mBaseDist_s{};
    // static_param at offset 0x40
    const float* mOutDist_s{};
    // static_param at offset 0x48
    const float* mSpeed_s{};
    // static_param at offset 0x50
    const float* mUpdateCircleMoveDistance_s{};
};

}  // namespace uking::ai
