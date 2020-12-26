#pragma once

#include "Game/AI/Action/actionNavMeshAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantNavMeshWalkWithVibration : public NavMeshAction {
    SEAD_RTTI_OVERRIDE(GiantNavMeshWalkWithVibration, NavMeshAction)
public:
    explicit GiantNavMeshWalkWithVibration(const InitArg& arg);
    ~GiantNavMeshWalkWithVibration() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    const float* mVibrationPower_s{};
};

}  // namespace uking::action
