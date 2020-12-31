#pragma once

#include "Game/AI/AI/aiHorseRideChaseBattleMoveBase.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class HorseRideChaseBattleMove : public HorseRideChaseBattleMoveBase {
    SEAD_RTTI_OVERRIDE(HorseRideChaseBattleMove, HorseRideChaseBattleMoveBase)
public:
    explicit HorseRideChaseBattleMove(const InitArg& arg);
    ~HorseRideChaseBattleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
