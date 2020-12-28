#include "Game/AI/Action/actionPlayerBindSheikPad.h"

namespace uking::action {

PlayerBindSheikPad::PlayerBindSheikPad(const InitArg& arg) : PlayerAction(arg) {}

PlayerBindSheikPad::~PlayerBindSheikPad() = default;

bool PlayerBindSheikPad::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerBindSheikPad::loadParams_() {}

}  // namespace uking::action
