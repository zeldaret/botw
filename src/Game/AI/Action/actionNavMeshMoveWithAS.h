#pragma once

#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshMoveWithAS : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(NavMeshMoveWithAS, NavMeshAction)
public:
    explicit NavMeshMoveWithAS(const InitArg& arg);
    ~NavMeshMoveWithAS() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // static_param at offset 0xa8
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0xb0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
