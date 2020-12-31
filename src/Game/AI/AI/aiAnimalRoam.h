#pragma once

#include "Game/AI/AI/aiAnimalRoamBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AnimalRoam : public AnimalRoamBase {
    SEAD_RTTI_OVERRIDE(AnimalRoam, AnimalRoamBase)
public:
    explicit AnimalRoam(const InitArg& arg);
    ~AnimalRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xa8
    const int* mFinishChangeCount_s{};
    // static_param at offset 0xb0
    const float* mLimitRadius_s{};
    // static_param at offset 0xb8
    const float* mChangeWaitRate_s{};
    // static_param at offset 0xc0
    const float* mFramesStuckOnTerrainAction_s{};
    // static_param at offset 0xc8
    const bool* mIsSendGoalPos_s{};
    // static_param at offset 0xd0
    const bool* mCheckValidStartPos_s{};
    // static_param at offset 0xd8
    const bool* mCheckLOS_s{};
};

}  // namespace uking::ai
