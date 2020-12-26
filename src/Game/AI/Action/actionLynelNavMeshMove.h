#pragma once

#include "Game/AI/Action/actionAnimalMoveGuidedBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LynelNavMeshMove : public AnimalMoveGuidedBase {
    SEAD_RTTI_OVERRIDE(LynelNavMeshMove, AnimalMoveGuidedBase)
public:
    explicit LynelNavMeshMove(const InitArg& arg);
    ~LynelNavMeshMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
