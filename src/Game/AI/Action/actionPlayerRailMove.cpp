#include "Game/AI/Action/actionPlayerRailMove.h"

namespace uking::action {

PlayerRailMove::PlayerRailMove(const InitArg& arg) : PlayerGuidedMove(arg) {}

PlayerRailMove::~PlayerRailMove() = default;

void PlayerRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerGuidedMove::enter_(params);
}

void PlayerRailMove::leave_() {
    PlayerGuidedMove::leave_();
}

void PlayerRailMove::loadParams_() {
    PlayerGuidedMove::loadParams_();
    getDynamicParam(&mRailName_d, "RailName");
}

void PlayerRailMove::calc_() {
    PlayerGuidedMove::calc_();
}

}  // namespace uking::action
