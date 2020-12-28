#pragma once

#include "Game/AI/Action/actionChemicalPhysBall.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChemicalPhysHitBreakBall : public ChemicalPhysBall {
    SEAD_RTTI_OVERRIDE(ChemicalPhysHitBreakBall, ChemicalPhysBall)
public:
    explicit ChemicalPhysHitBreakBall(const InitArg& arg);
    ~ChemicalPhysHitBreakBall() override;

protected:
};

}  // namespace uking::action
