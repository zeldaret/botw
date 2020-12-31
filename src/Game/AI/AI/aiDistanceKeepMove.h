#pragma once

#include "Game/AI/AI/aiWaitNearTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DistanceKeepMove : public WaitNearTarget {
    SEAD_RTTI_OVERRIDE(DistanceKeepMove, WaitNearTarget)
public:
    explicit DistanceKeepMove(const InitArg& arg);
    ~DistanceKeepMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x68
    const float* mStartBackDistOffset_s{};
};

}  // namespace uking::ai
