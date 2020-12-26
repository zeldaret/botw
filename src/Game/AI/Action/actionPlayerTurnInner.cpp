#include "Game/AI/Action/actionPlayerTurnInner.h"

namespace uking::action {

PlayerTurnInner::PlayerTurnInner(const InitArg& arg) : PlayerAction(arg) {}

PlayerTurnInner::~PlayerTurnInner() = default;

bool PlayerTurnInner::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerTurnInner::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerTurnInner::leave_() {
    PlayerAction::leave_();
}

void PlayerTurnInner::loadParams_() {}

void PlayerTurnInner::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
