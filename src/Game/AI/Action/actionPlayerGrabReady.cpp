#include "Game/AI/Action/actionPlayerGrabReady.h"

namespace uking::action {

PlayerGrabReady::PlayerGrabReady(const InitArg& arg) : PlayerAction(arg) {}

PlayerGrabReady::~PlayerGrabReady() = default;

bool PlayerGrabReady::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerGrabReady::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabReady::leave_() {
    PlayerAction::leave_();
}

void PlayerGrabReady::loadParams_() {}

void PlayerGrabReady::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
