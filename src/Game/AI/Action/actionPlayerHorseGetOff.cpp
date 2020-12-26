#include "Game/AI/Action/actionPlayerHorseGetOff.h"

namespace uking::action {

PlayerHorseGetOff::PlayerHorseGetOff(const InitArg& arg) : PlayerAction(arg) {}

PlayerHorseGetOff::~PlayerHorseGetOff() = default;

bool PlayerHorseGetOff::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerHorseGetOff::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerHorseGetOff::leave_() {
    PlayerAction::leave_();
}

void PlayerHorseGetOff::loadParams_() {
    getStaticParam(&mSideFallSpeed_s, "SideFallSpeed");
}

void PlayerHorseGetOff::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
