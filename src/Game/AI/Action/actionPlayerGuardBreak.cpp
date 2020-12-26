#include "Game/AI/Action/actionPlayerGuardBreak.h"

namespace uking::action {

PlayerGuardBreak::PlayerGuardBreak(const InitArg& arg) : PlayerAction(arg) {}

PlayerGuardBreak::~PlayerGuardBreak() = default;

bool PlayerGuardBreak::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerGuardBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGuardBreak::leave_() {
    PlayerAction::leave_();
}

void PlayerGuardBreak::loadParams_() {}

void PlayerGuardBreak::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
