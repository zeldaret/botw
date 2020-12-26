#include "Game/AI/Action/actionPlayerHorseGetOffInDemo.h"

namespace uking::action {

PlayerHorseGetOffInDemo::PlayerHorseGetOffInDemo(const InitArg& arg) : PlayerAction(arg) {}

PlayerHorseGetOffInDemo::~PlayerHorseGetOffInDemo() = default;

bool PlayerHorseGetOffInDemo::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerHorseGetOffInDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHorseGetOffInDemo::leave_() {
    PlayerAction::leave_();
}

void PlayerHorseGetOffInDemo::loadParams_() {}

void PlayerHorseGetOffInDemo::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
