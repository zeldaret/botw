#pragma once

#include "Game/AI/Action/actionLevelFlyRiseLookingTarget.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LevelFlyLookRisingToTgtHeight : public LevelFlyRiseLookingTarget {
    SEAD_RTTI_OVERRIDE(LevelFlyLookRisingToTgtHeight, LevelFlyRiseLookingTarget)
public:
    explicit LevelFlyLookRisingToTgtHeight(const InitArg& arg);
    ~LevelFlyLookRisingToTgtHeight() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
