#include "Game/AI/Action/actionPlayerUnbindSheikPad.h"

namespace uking::action {

PlayerUnbindSheikPad::PlayerUnbindSheikPad(const InitArg& arg) : PlayerAction(arg) {}

PlayerUnbindSheikPad::~PlayerUnbindSheikPad() = default;

bool PlayerUnbindSheikPad::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerUnbindSheikPad::loadParams_() {}

}  // namespace uking::action
