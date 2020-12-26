#include "Game/AI/Action/actionPlayerLookAtTheFront.h"

namespace uking::action {

PlayerLookAtTheFront::PlayerLookAtTheFront(const InitArg& arg) : PlayerAction(arg) {}

PlayerLookAtTheFront::~PlayerLookAtTheFront() = default;

bool PlayerLookAtTheFront::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerLookAtTheFront::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerLookAtTheFront::leave_() {
    PlayerAction::leave_();
}

void PlayerLookAtTheFront::loadParams_() {
    getDynamicParam(&mIsValid_d, "IsValid");
}

void PlayerLookAtTheFront::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
