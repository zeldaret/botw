#include "Game/AI/Action/actionPlayerGrabThrow.h"

namespace uking::action {

PlayerGrabThrow::PlayerGrabThrow(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGrabThrow::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGrabThrow::leave_() {
    PlayerAction::leave_();
}

void PlayerGrabThrow::loadParams_() {
    getStaticParam(&mOverThrowSpeedYB_s, "OverThrowSpeedYB");
    getStaticParam(&mOverThrowSpeedFB_s, "OverThrowSpeedFB");
    getStaticParam(&mOverThrowSpeedYL_s, "OverThrowSpeedYL");
    getStaticParam(&mOverThrowSpeedFL_s, "OverThrowSpeedFL");
    getStaticParam(&mOverThrowInertiaRate_s, "OverThrowInertiaRate");
}

void PlayerGrabThrow::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
