#pragma once

#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshSlippedWalk : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(NavMeshSlippedWalk, NavMeshAction)
public:
    explicit NavMeshSlippedWalk(const InitArg& arg);
    ~NavMeshSlippedWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    const float* mAccRatio_s{};
    // static_param at offset 0xb0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
