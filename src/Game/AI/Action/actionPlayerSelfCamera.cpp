#include "Game/AI/Action/actionPlayerSelfCamera.h"

namespace uking::action {

PlayerSelfCamera::PlayerSelfCamera(const InitArg& arg) : PlayerAction(arg) {}

PlayerSelfCamera::~PlayerSelfCamera() = default;

bool PlayerSelfCamera::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSelfCamera::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSelfCamera::leave_() {
    PlayerAction::leave_();
}

void PlayerSelfCamera::loadParams_() {}

void PlayerSelfCamera::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
