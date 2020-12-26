#pragma once

#include "Game/AI/Action/actionLevelFlyMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SwarmLevelFlyMove : public LevelFlyMoveBase {
    SEAD_RTTI_OVERRIDE(SwarmLevelFlyMove, LevelFlyMoveBase)
public:
    explicit SwarmLevelFlyMove(const InitArg& arg);
    ~SwarmLevelFlyMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x138
    const int* mIgnoreSensorTime_s{};
    // static_param at offset 0x140
    const float* mSubAccRateMin_s{};
    // static_param at offset 0x148
    const float* mSubAccRateMax_s{};
    // static_param at offset 0x150
    const float* mMaterialAnimFrame_s{};
    // static_param at offset 0x158
    sead::SafeString mMaterialAnimName_s{};
};

}  // namespace uking::action
