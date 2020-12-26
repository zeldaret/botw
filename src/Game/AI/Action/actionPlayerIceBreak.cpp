#include "Game/AI/Action/actionPlayerIceBreak.h"

namespace uking::action {

PlayerIceBreak::PlayerIceBreak(const InitArg& arg) : PlayerAction(arg) {}

PlayerIceBreak::~PlayerIceBreak() = default;

bool PlayerIceBreak::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerIceBreak::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerIceBreak::leave_() {
    PlayerAction::leave_();
}

void PlayerIceBreak::loadParams_() {}

void PlayerIceBreak::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
