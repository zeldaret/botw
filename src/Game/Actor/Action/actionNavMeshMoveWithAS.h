#pragma once

#include "Game/Actor/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshMoveWithAS : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(NavMeshMoveWithAS, NavMeshMoveBase)
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
