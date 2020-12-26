#include "Game/AI/Action/actionPlayerSitEnd.h"

namespace uking::action {

PlayerSitEnd::PlayerSitEnd(const InitArg& arg) : PlayerAction(arg) {}

PlayerSitEnd::~PlayerSitEnd() = default;

bool PlayerSitEnd::init_(sead::Heap* heap) {
    return PlayerAction::init_(heap);
}

void PlayerSitEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerSitEnd::leave_() {
    PlayerAction::leave_();
}

void PlayerSitEnd::loadParams_() {}

void PlayerSitEnd::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
