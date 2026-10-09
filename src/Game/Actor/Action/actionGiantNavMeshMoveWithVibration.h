#pragma once

#include "Game/Actor/Action/actionNavMeshMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantNavMeshMoveWithVibration : public NavMeshMoveBase {
    SEAD_RTTI_OVERRIDE(GiantNavMeshMoveWithVibration, NavMeshMoveBase)
public:
    explicit GiantNavMeshMoveWithVibration(const InitArg& arg);
    ~GiantNavMeshMoveWithVibration() override;

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
