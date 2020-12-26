#pragma once

#include "Game/AI/Action/actionGiantEnemyWalkWithVibration.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantEnemyWalk : public GiantEnemyWalkWithVibration {
    SEAD_RTTI_OVERRIDE(GiantEnemyWalk, GiantEnemyWalkWithVibration)
public:
    explicit GiantEnemyWalk(const InitArg& arg);
    ~GiantEnemyWalk() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
