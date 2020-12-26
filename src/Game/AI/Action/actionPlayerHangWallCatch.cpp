#include "Game/AI/Action/actionPlayerHangWallCatch.h"

namespace uking::action {

PlayerHangWallCatch::PlayerHangWallCatch(const InitArg& arg) : PlayerAction(arg) {}

PlayerHangWallCatch::~PlayerHangWallCatch() = default;

bool PlayerHangWallCatch::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerHangWallCatch::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHangWallCatch::leave_() {
    PlayerAction::leave_();
}

void PlayerHangWallCatch::loadParams_() {}

void PlayerHangWallCatch::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
