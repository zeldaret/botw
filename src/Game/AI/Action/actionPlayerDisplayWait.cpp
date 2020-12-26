#include "Game/AI/Action/actionPlayerDisplayWait.h"

namespace uking::action {

PlayerDisplayWait::PlayerDisplayWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerDisplayWait::~PlayerDisplayWait() = default;

bool PlayerDisplayWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerDisplayWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDisplayWait::leave_() {
    PlayerAction::leave_();
}

void PlayerDisplayWait::loadParams_() {}

void PlayerDisplayWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
