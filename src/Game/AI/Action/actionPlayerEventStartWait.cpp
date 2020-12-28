#include "Game/AI/Action/actionPlayerEventStartWait.h"

namespace uking::action {

PlayerEventStartWait::PlayerEventStartWait(const InitArg& arg) : PlayerAction(arg) {}

PlayerEventStartWait::~PlayerEventStartWait() = default;

void PlayerEventStartWait::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerEventStartWait::leave_() {
    PlayerAction::leave_();
}

void PlayerEventStartWait::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
