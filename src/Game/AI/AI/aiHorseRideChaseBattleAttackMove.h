#pragma once

#include "Game/AI/AI/aiHorseRideChaseBattleMoveBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideChaseBattleAttackMove : public HorseRideChaseBattleMoveBase {
    SEAD_RTTI_OVERRIDE(HorseRideChaseBattleAttackMove, HorseRideChaseBattleMoveBase)
public:
    explicit HorseRideChaseBattleAttackMove(const InitArg& arg);
    ~HorseRideChaseBattleAttackMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
