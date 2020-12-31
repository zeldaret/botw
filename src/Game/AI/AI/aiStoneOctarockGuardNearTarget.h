#pragma once

#include "Game/AI/AI/aiTimedGuardNearTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StoneOctarockGuardNearTarget : public TimedGuardNearTarget {
    SEAD_RTTI_OVERRIDE(StoneOctarockGuardNearTarget, TimedGuardNearTarget)
public:
    explicit StoneOctarockGuardNearTarget(const InitArg& arg);
    ~StoneOctarockGuardNearTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xb0
    const int* mNoticeTerrorLevel_s{};
};

}  // namespace uking::ai
