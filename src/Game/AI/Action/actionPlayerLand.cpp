#include "Game/AI/Action/actionPlayerLand.h"

namespace uking::action {

PlayerLand::PlayerLand(const InitArg& arg) : PlayerAction(arg) {}

PlayerLand::~PlayerLand() = default;

bool PlayerLand::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLand::leave_() {
    PlayerAction::leave_();
}

void PlayerLand::loadParams_() {}

void PlayerLand::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
