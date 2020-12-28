#pragma once

#include "Game/AI/Action/actionAnimalMoveGuidedBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class HorseMoveToTargetAction : public AnimalMoveGuidedBase {
    SEAD_RTTI_OVERRIDE(HorseMoveToTargetAction, AnimalMoveGuidedBase)
public:
    explicit HorseMoveToTargetAction(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x78
    const bool* mIsCancelRequestedPathFirst_s{};
    // dynamic_param at offset 0x80
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
