#include "Game/AI/Action/actionPlayerBindSheikPad.h"

namespace uking::action {

PlayerBindSheikPad::PlayerBindSheikPad(const InitArg& arg) : PlayerAction(arg) {}

PlayerBindSheikPad::~PlayerBindSheikPad() = default;

bool PlayerBindSheikPad::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerBindSheikPad::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerBindSheikPad::leave_() {
    PlayerAction::leave_();
}

void PlayerBindSheikPad::loadParams_() {}

void PlayerBindSheikPad::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
