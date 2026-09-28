#pragma once

#include "Game/Actor/Action/actionMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantEnemyMoveWithVibration : public MoveBase {
    SEAD_RTTI_OVERRIDE(GiantEnemyMoveWithVibration, MoveBase)
public:
    explicit GiantEnemyMoveWithVibration(const InitArg& arg);
    ~GiantEnemyMoveWithVibration() override;

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
