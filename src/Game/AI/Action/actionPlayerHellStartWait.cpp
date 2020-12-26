#include "Game/AI/Action/actionPlayerHellStartWait.h"

namespace uking::action {

PlayerHellStartWait::PlayerHellStartWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerHellStartWait::~PlayerHellStartWait() = default;

bool PlayerHellStartWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerHellStartWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHellStartWait::leave_() {
    PlayerAction::leave_();
}

void PlayerHellStartWait::loadParams_() {}

void PlayerHellStartWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
