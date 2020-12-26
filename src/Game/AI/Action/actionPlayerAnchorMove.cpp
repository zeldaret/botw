#include "Game/AI/Action/actionPlayerAnchorMove.h"

namespace uking::action {

PlayerAnchorMove::PlayerAnchorMove(const InitArg& arg) : PlayerGuidedMove(arg) {}

PlayerAnchorMove::~PlayerAnchorMove() = default;

bool PlayerAnchorMove::init_(sead::Heap* heap) {
    return PlayerGuidedMove::init_(heap);
}

void PlayerAnchorMove::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerGuidedMove::enter_(params);
}

void PlayerAnchorMove::leave_() {
    PlayerGuidedMove::leave_();
}

void PlayerAnchorMove::loadParams_() {
    PlayerGuidedMove::loadParams_();
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

void PlayerAnchorMove::calc_() {
    PlayerGuidedMove::calc_();
}

}  // namespace uking::action
