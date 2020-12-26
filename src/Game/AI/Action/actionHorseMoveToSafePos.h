#pragma once

#include "Game/AI/Action/actionAnimalMoveGuidedBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseMoveToSafePos : public AnimalMoveGuidedBase {
    SEAD_RTTI_OVERRIDE(HorseMoveToSafePos, AnimalMoveGuidedBase)
public:
    explicit HorseMoveToSafePos(const InitArg& arg);
    ~HorseMoveToSafePos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const float* mSearchRadius_s{};
    // static_param at offset 0x80
    const float* mAreaThreshold_s{};
    // static_param at offset 0x88
    const float* mResolvePenetrationRadiusScale_s{};
    // static_param at offset 0x90
    const float* mResolvePenetrationSearchRadius_s{};
    // static_param at offset 0x98
    const bool* mSetEndIfCurrentFaceIsSafe_s{};
};

}  // namespace uking::action
