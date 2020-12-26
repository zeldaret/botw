#include "Game/AI/Action/actionPlayerLadderUpEnd.h"

namespace uking::action {

PlayerLadderUpEnd::PlayerLadderUpEnd(const InitArg& arg) : PlayerAction(arg) {}

PlayerLadderUpEnd::~PlayerLadderUpEnd() = default;

bool PlayerLadderUpEnd::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerLadderUpEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLadderUpEnd::leave_() {
    PlayerAction::leave_();
}

void PlayerLadderUpEnd::loadParams_() {}

void PlayerLadderUpEnd::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
