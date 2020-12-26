#include "Game/AI/Action/actionPlayerEventStartWait.h"

namespace uking::action {

PlayerEventStartWait::PlayerEventStartWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerEventStartWait::~PlayerEventStartWait() = default;

bool PlayerEventStartWait::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerEventStartWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerEventStartWait::leave_() {
    PlayerAction::leave_();
}

void PlayerEventStartWait::loadParams_() {}

void PlayerEventStartWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
