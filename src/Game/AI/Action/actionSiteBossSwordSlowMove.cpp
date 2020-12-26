#include "Game/AI/Action/actionSiteBossSwordSlowMove.h"

namespace uking::action {

SiteBossSwordSlowMove::SiteBossSwordSlowMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossSwordSlowMove::~SiteBossSwordSlowMove() = default;

bool SiteBossSwordSlowMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSwordSlowMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossSwordSlowMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossSwordSlowMove::loadParams_() {
    getStaticParam(&mAfterImage0AppearFrame_s, "AfterImage0AppearFrame");
    getStaticParam(&mAfterImage1AppearFrame_s, "AfterImage1AppearFrame");
    getStaticParam(&mAppearFrame_s, "AppearFrame");
    getDynamicParam(&mCurrentFrame_d, "CurrentFrame");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
    getDynamicParam(&mAfterImage0Pos_d, "AfterImage0Pos");
    getDynamicParam(&mAfterImage1Pos_d, "AfterImage1Pos");
}

void SiteBossSwordSlowMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
