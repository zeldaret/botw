#include "Game/AI/Action/actionPlayerGrabUp.h"

namespace uking::action {

PlayerGrabUp::PlayerGrabUp(const InitArg& arg) : PlayerAction(arg) {}

PlayerGrabUp::~PlayerGrabUp() = default;

bool PlayerGrabUp::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerGrabUp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabUp::leave_() {
    PlayerAction::leave_();
}

void PlayerGrabUp::loadParams_() {}

void PlayerGrabUp::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
