#include "Game/AI/Action/actionPlayerIceGrabReady.h"

namespace uking::action {

PlayerIceGrabReady::PlayerIceGrabReady(const InitArg& arg) : PlayerAction(arg) {}

PlayerIceGrabReady::~PlayerIceGrabReady() = default;

bool PlayerIceGrabReady::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerIceGrabReady::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerIceGrabReady::leave_() {
    PlayerAction::leave_();
}

void PlayerIceGrabReady::loadParams_() {}

void PlayerIceGrabReady::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
