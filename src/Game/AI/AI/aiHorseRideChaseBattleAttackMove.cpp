#include "Game/AI/AI/aiHorseRideChaseBattleAttackMove.h"

namespace uking::ai {

HorseRideChaseBattleAttackMove::HorseRideChaseBattleAttackMove(const InitArg& arg)
    : HorseRideChaseBattleMoveBase(arg) {}

HorseRideChaseBattleAttackMove::~HorseRideChaseBattleAttackMove() = default;

bool HorseRideChaseBattleAttackMove::init_(sead::Heap* heap) {
    return HorseRideChaseBattleMoveBase::init_(heap);
}

void HorseRideChaseBattleAttackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideChaseBattleMoveBase::enter_(params);
}

void HorseRideChaseBattleAttackMove::leave_() {
    HorseRideChaseBattleMoveBase::leave_();
}

void HorseRideChaseBattleAttackMove::loadParams_() {
    HorseRideChaseBattleMoveBase::loadParams_();
}

}  // namespace uking::ai
