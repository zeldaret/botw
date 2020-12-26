#pragma once

#include "Game/AI/Action/actionRandomMoveAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyRushAttack : public RandomMoveAction {
    SEAD_RTTI_OVERRIDE(EnemyRushAttack, RandomMoveAction)
public:
    explicit EnemyRushAttack(const InitArg& arg);
    ~EnemyRushAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x38
    const int* mUpdateTargetPosInterval_s{};
    // static_param at offset 0x40
    const float* mSpeed_s{};
    // static_param at offset 0x48
    const float* mDisableUpdateTargetRadius_s{};
    // static_param at offset 0x50
    const float* mGoalDistanceTolerance_s{};
    // static_param at offset 0x58
    const float* mMovePredictionRate_s{};
    // static_param at offset 0x60
    sead::SafeString mASKeyName_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
