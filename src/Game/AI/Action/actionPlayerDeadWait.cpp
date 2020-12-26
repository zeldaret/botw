#include "Game/AI/Action/actionPlayerDeadWait.h"

namespace uking::action {

PlayerDeadWait::PlayerDeadWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerDeadWait::~PlayerDeadWait() = default;

bool PlayerDeadWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerDeadWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDeadWait::leave_() {
    PlayerAction::leave_();
}

void PlayerDeadWait::loadParams_() {}

void PlayerDeadWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
