#include "Game/AI/Action/actionPlayerHangWallCatch.h"

namespace uking::action {

PlayerHangWallCatch::PlayerHangWallCatch(const InitArg& arg) : PlayerAction(arg) {}

void PlayerHangWallCatch::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHangWallCatch::leave_() {
    PlayerAction::leave_();
}

void PlayerHangWallCatch::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
