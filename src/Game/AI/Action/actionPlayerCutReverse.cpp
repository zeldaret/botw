#include "Game/AI/Action/actionPlayerCutReverse.h"

namespace uking::action {

PlayerCutReverse::PlayerCutReverse(const InitArg& arg) : PlayerAction(arg) {}

PlayerCutReverse::~PlayerCutReverse() = default;

bool PlayerCutReverse::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerCutReverse::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerCutReverse::leave_() {
    PlayerAction::leave_();
}

void PlayerCutReverse::loadParams_() {}

void PlayerCutReverse::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
