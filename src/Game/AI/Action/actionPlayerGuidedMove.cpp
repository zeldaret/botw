#include "Game/AI/Action/actionPlayerGuidedMove.h"

namespace uking::action {

PlayerGuidedMove::PlayerGuidedMove(const InitArg& arg) : PlayerAction(arg) {}

void PlayerGuidedMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerGuidedMove::leave_() {
    PlayerAction::leave_();
}

void PlayerGuidedMove::loadParams_() {
    getStaticParam(&mDecSpdDist_s, "DecSpdDist");
    getDynamicParam(&mStickValue_d, "StickValue");
    getStaticParam(&mForceTurnDist_s, "ForceTurnDist");
}

void PlayerGuidedMove::calc_() {
    PlayerAction::calc_();
}

}  // namespace uking::action
