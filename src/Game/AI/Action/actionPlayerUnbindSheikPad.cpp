#include "Game/AI/Action/actionPlayerUnbindSheikPad.h"

namespace uking::action {

PlayerUnbindSheikPad::PlayerUnbindSheikPad(const InitArg& arg) : PlayerAction(arg) {}

PlayerUnbindSheikPad::~PlayerUnbindSheikPad() = default;

bool PlayerUnbindSheikPad::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerUnbindSheikPad::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerUnbindSheikPad::leave_() {
    PlayerAction::leave_();
}

void PlayerUnbindSheikPad::loadParams_() {}

void PlayerUnbindSheikPad::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
