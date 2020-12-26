#include "Game/AI/Action/actionForkFollowGround.h"

namespace uking::action {

ForkFollowGround::ForkFollowGround(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkFollowGround::~ForkFollowGround() = default;

bool ForkFollowGround::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkFollowGround::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkFollowGround::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkFollowGround::loadParams_() {
    getStaticParam(&mUpdateFrameCountAfterNoMove_s, "UpdateFrameCountAfterNoMove");
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mUpdateTargetUpDirMinAngle_s, "UpdateTargetUpDirMinAngle");
    getStaticParam(&mUpdateTargetUpDirRatio_s, "UpdateTargetUpDirRatio");
}

void ForkFollowGround::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
