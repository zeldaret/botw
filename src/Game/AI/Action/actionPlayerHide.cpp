#include "Game/AI/Action/actionPlayerHide.h"

namespace uking::action {

PlayerHide::PlayerHide(const InitArg& arg) : PlayerAction(arg) {}

PlayerHide::~PlayerHide() = default;

bool PlayerHide::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerHide::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHide::leave_() {
    PlayerAction::leave_();
}

void PlayerHide::loadParams_() {
    getStaticParam(&mHidden_s, "Hidden");
}

void PlayerHide::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
