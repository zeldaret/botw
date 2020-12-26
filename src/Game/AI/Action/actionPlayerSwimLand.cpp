#include "Game/AI/Action/actionPlayerSwimLand.h"

namespace uking::action {

PlayerSwimLand::PlayerSwimLand(const InitArg& arg) : PlayerAction(arg) {}

PlayerSwimLand::~PlayerSwimLand() = default;

bool PlayerSwimLand::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSwimLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSwimLand::leave_() {
    PlayerAction::leave_();
}

void PlayerSwimLand::loadParams_() {}

void PlayerSwimLand::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
