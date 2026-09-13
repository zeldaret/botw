#pragma once

#include "Game/Actor/Horse/Action/actionAnimalMoveGuidedBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AnimalNavMeshMove : public AnimalMoveGuidedBase {
    SEAD_RTTI_OVERRIDE(AnimalNavMeshMove, AnimalMoveGuidedBase)
public:
    explicit AnimalNavMeshMove(const InitArg& arg);
    ~AnimalNavMeshMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
