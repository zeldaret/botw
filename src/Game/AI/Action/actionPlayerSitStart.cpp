#include "Game/AI/Action/actionPlayerSitStart.h"

namespace uking::action {

PlayerSitStart::PlayerSitStart(const InitArg& arg) : PlayerAction(arg) {}

PlayerSitStart::~PlayerSitStart() = default;

bool PlayerSitStart::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSitStart::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSitStart::leave_() {
    PlayerAction::leave_();
}

void PlayerSitStart::loadParams_() {}

void PlayerSitStart::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
