#pragma once

#include "Game/AI/Action/actionLevelFlyMove.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class InsectLevelFlyMove : public LevelFlyMove {
    SEAD_RTTI_OVERRIDE(InsectLevelFlyMove, LevelFlyMove)
public:
    explicit InsectLevelFlyMove(const InitArg& arg);
    ~InsectLevelFlyMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x148
    const float* mReduceSpeedRateWithWind_s{};
    // static_param at offset 0x150
    const float* mWindVelocityLimit4Reduce_s{};
};

}  // namespace uking::action
