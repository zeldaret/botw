#include "Game/AI/Action/actionPlayerCutDash.h"

namespace uking::action {

PlayerCutDash::PlayerCutDash(const InitArg& arg) : PlayerAction(arg) {}

PlayerCutDash::~PlayerCutDash() = default;

bool PlayerCutDash::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerCutDash::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutDash::leave_() {
    PlayerAction::leave_();
}

void PlayerCutDash::loadParams_() {
    getStaticParam(&mSearchAngle_s, "SearchAngle");
}

void PlayerCutDash::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
