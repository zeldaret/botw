#include "Game/AI/Action/actionSiteBossSwordMove.h"

namespace uking::action {

SiteBossSwordMove::SiteBossSwordMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SiteBossSwordMove::~SiteBossSwordMove() = default;

bool SiteBossSwordMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossSwordMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossSwordMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossSwordMove::loadParams_() {
    getStaticParam(&mAfterImage0AppearFrame_s, "AfterImage0AppearFrame");
    getStaticParam(&mAfterImage1AppearFrame_s, "AfterImage1AppearFrame");
    getStaticParam(&mAppearFrame_s, "AppearFrame");
    getDynamicParam(&mCurrentFrame_d, "CurrentFrame");
    getDynamicParam(&mIsCloseMove_d, "IsCloseMove");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveDstPos_d, "MoveDstPos");
    getDynamicParam(&mAfterImage0Pos_d, "AfterImage0Pos");
    getDynamicParam(&mAfterImage1Pos_d, "AfterImage1Pos");
}

void SiteBossSwordMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
