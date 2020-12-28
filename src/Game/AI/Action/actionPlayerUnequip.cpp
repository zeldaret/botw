#include "Game/AI/Action/actionPlayerUnequip.h"

namespace uking::action {

PlayerUnequip::PlayerUnequip(const InitArg& arg) : PlayerAction(arg) {}

PlayerUnequip::~PlayerUnequip() = default;

bool PlayerUnequip::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerUnequip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerUnequip::leave_() {
    PlayerAction::leave_();
}

void PlayerUnequip::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
