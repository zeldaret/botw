#pragma once

#include "Game/AI/AI/aiNavMoveTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChuchuNavMoveTarget : public NavMoveTarget {
    SEAD_RTTI_OVERRIDE(ChuchuNavMoveTarget, NavMoveTarget)
public:
    explicit ChuchuNavMoveTarget(const InitArg& arg);
    ~ChuchuNavMoveTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x380
    const int* mWallHitTime_s{};
};

}  // namespace uking::ai
