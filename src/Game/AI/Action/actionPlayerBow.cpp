#include "Game/AI/Action/actionPlayerBow.h"

namespace uking::action {

PlayerBow::PlayerBow(const InitArg& arg) : PlayerAction(arg) {}

PlayerBow::~PlayerBow() = default;

bool PlayerBow::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerBow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerBow::leave_() {
    PlayerAction::leave_();
}

void PlayerBow::loadParams_() {}

void PlayerBow::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
