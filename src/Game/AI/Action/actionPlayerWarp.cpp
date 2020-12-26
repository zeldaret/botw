#include "Game/AI/Action/actionPlayerWarp.h"

namespace uking::action {

PlayerWarp::PlayerWarp(const InitArg& arg) : PlayerAction(arg) {}

PlayerWarp::~PlayerWarp() = default;

bool PlayerWarp::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerWarp::leave_() {
    PlayerAction::leave_();
}

void PlayerWarp::loadParams_() {}

void PlayerWarp::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
