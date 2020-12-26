#pragma once

#include "Game/AI/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantEnemyWalkWithVibration : public MoveBase {
    SEAD_RTTI_OVERRIDE(GiantEnemyWalkWithVibration, MoveBase)
public:
    explicit GiantEnemyWalkWithVibration(const InitArg& arg);
    ~GiantEnemyWalkWithVibration() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xe0
    const float* mVibrationPower_s{};
};

}  // namespace uking::action
