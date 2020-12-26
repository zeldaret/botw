#include "Game/AI/Action/actionSiteBossSwordAfterImageMove.h"

namespace uking::action {

SiteBossSwordAfterImageMove::SiteBossSwordAfterImageMove(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossSwordAfterImageMove::~SiteBossSwordAfterImageMove() = default;

bool SiteBossSwordAfterImageMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSwordAfterImageMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossSwordAfterImageMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossSwordAfterImageMove::loadParams_() {
    getStaticParam(&mMoveFrame_s, "MoveFrame");
    getMapUnitParam(&mPatternID_m, "PatternID");
    getAITreeVariable(&mSiteBossSwordAfterImageUnit_a, "SiteBossSwordAfterImageUnit");
}

void SiteBossSwordAfterImageMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
