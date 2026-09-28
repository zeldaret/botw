#pragma once

#include "Game/Actor/AI/aiInvincibleNearTarget.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StoneOctarockGuardNearTarget : public InvincibleNearTarget {
    SEAD_RTTI_OVERRIDE(StoneOctarockGuardNearTarget, InvincibleNearTarget)
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
