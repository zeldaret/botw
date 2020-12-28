#pragma once

#include "Game/AI/Action/actionNavMeshWalk.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMiniGuardNavMeshWalk : public NavMeshWalk {
    SEAD_RTTI_OVERRIDE(GuardianMiniGuardNavMeshWalk, NavMeshWalk)
public:
    explicit GuardianMiniGuardNavMeshWalk(const InitArg& arg);
    ~GuardianMiniGuardNavMeshWalk() override;

    void loadParams_() override;

protected:
    // static_param at offset 0xa8
    const int* mASSlot_s{};
    // static_param at offset 0xb0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
