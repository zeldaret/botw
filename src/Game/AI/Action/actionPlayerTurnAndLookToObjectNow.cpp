#include "Game/AI/Action/actionPlayerTurnAndLookToObjectNow.h"

namespace uking::action {

PlayerTurnAndLookToObjectNow::PlayerTurnAndLookToObjectNow(const InitArg& arg)
    : PlayerLookAtObjectNow(arg) {}

PlayerTurnAndLookToObjectNow::~PlayerTurnAndLookToObjectNow() = default;

bool PlayerTurnAndLookToObjectNow::init_(sead::Heap* heap) {
    return PlayerLookAtObjectNow::init_(heap);
}

void PlayerTurnAndLookToObjectNow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerLookAtObjectNow::enter_(params);
}

void PlayerTurnAndLookToObjectNow::leave_() {
    PlayerLookAtObjectNow::leave_();
}

void PlayerTurnAndLookToObjectNow::loadParams_() {
    PlayerLookAtObjectNow::loadParams_();
}

void PlayerTurnAndLookToObjectNow::calc_() {
    PlayerLookAtObjectNow::calc_();
}

}  // namespace uking::action
