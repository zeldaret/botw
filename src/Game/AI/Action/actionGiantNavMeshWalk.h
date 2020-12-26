#pragma once

#include "Game/AI/Action/actionGiantNavMeshWalkWithVibration.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantNavMeshWalk : public GiantNavMeshWalkWithVibration {
    SEAD_RTTI_OVERRIDE(GiantNavMeshWalk, GiantNavMeshWalkWithVibration)
public:
    explicit GiantNavMeshWalk(const InitArg& arg);
    ~GiantNavMeshWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
