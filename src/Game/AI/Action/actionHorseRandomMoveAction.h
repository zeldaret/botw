#pragma once

#include "Game/AI/Action/actionAnimalMoveGuidedBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseRandomMoveAction : public AnimalMoveGuidedBase {
    SEAD_RTTI_OVERRIDE(HorseRandomMoveAction, AnimalMoveGuidedBase)
public:
    explicit HorseRandomMoveAction(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    // static_param at offset 0x78
    const float* mRadiusLimit_s{};
    // static_param at offset 0x80
    const float* mForwardDirDistCoefficient_s{};
    // static_param at offset 0x88
    const float* mDirRandomValue_s{};
    // static_param at offset 0x90
    const float* mDirRangeDegree_s{};
    // static_param at offset 0x98
    const float* mRejectDistRatioByNavMeshQuery_s{};
    // static_param at offset 0xa0
    const bool* mIsCancelRequestedPathFirst_s{};
};

}  // namespace uking::action
