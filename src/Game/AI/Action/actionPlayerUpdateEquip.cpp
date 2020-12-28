#include "Game/AI/Action/actionPlayerUpdateEquip.h"

namespace uking::action {

PlayerUpdateEquip::PlayerUpdateEquip(const InitArg& arg) : PlayerAction(arg) {}

PlayerUpdateEquip::~PlayerUpdateEquip() = default;

bool PlayerUpdateEquip::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerUpdateEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerUpdateEquip::leave_() {
    PlayerAction::leave_();
}

void PlayerUpdateEquip::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
