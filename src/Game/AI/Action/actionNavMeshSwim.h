#pragma once

#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class NavMeshSwim : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(NavMeshSwim, NavMeshAction)
public:
    explicit NavMeshSwim(const InitArg& arg);
    ~NavMeshSwim() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    const float* mInWaterDepth_s{};
    // static_param at offset 0xb0
    const float* mFloatDepth_s{};
    // static_param at offset 0xb8
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
