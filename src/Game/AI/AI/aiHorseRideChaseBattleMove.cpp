#include "Game/AI/AI/aiHorseRideChaseBattleMove.h"

namespace uking::ai {

HorseRideChaseBattleMove::HorseRideChaseBattleMove(const InitArg& arg)
    : HorseRideChaseBattleMoveBase(arg) {}

HorseRideChaseBattleMove::~HorseRideChaseBattleMove() = default;

bool HorseRideChaseBattleMove::init_(sead::Heap* heap) {
    return HorseRideChaseBattleMoveBase::init_(heap);
}

void HorseRideChaseBattleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideChaseBattleMoveBase::enter_(params);
}

void HorseRideChaseBattleMove::leave_() {
    HorseRideChaseBattleMoveBase::leave_();
}

void HorseRideChaseBattleMove::loadParams_() {
    HorseRideChaseBattleMoveBase::loadParams_();
}

}  // namespace uking::ai
