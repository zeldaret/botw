#include "Game/AI/Action/actionPlayerSlideLand.h"

namespace uking::action {

PlayerSlideLand::PlayerSlideLand(const InitArg& arg) : PlayerAction(arg) {}

PlayerSlideLand::~PlayerSlideLand() = default;

bool PlayerSlideLand::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSlideLand::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSlideLand::leave_() {
    PlayerAction::leave_();
}

void PlayerSlideLand::loadParams_() {}

void PlayerSlideLand::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
