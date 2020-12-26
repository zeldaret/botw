#include "Game/AI/Action/actionForkASTrgShootArrowWithBaseBone.h"

namespace uking::action {

ForkASTrgShootArrowWithBaseBone::ForkASTrgShootArrowWithBaseBone(const InitArg& arg)
    : ForkASTrgShootArrow(arg) {}

ForkASTrgShootArrowWithBaseBone::~ForkASTrgShootArrowWithBaseBone() = default;

bool ForkASTrgShootArrowWithBaseBone::init_(sead::Heap* heap) {
    return ForkASTrgShootArrow::init_(heap);
}

void ForkASTrgShootArrowWithBaseBone::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASTrgShootArrow::enter_(params);
}

void ForkASTrgShootArrowWithBaseBone::leave_() {
    ForkASTrgShootArrow::leave_();
}

void ForkASTrgShootArrowWithBaseBone::loadParams_() {
    ForkASTrgShootArrow::loadParams_();
    getStaticParam(&mFrontDirAngle_s, "FrontDirAngle");
    getStaticParam(&mIsAddTargetActorAimPosHeight_s, "IsAddTargetActorAimPosHeight");
    getStaticParam(&mBaseBoneName_s, "BaseBoneName");
    getStaticParam(&mFrontDirOfBaseBone_s, "FrontDirOfBaseBone");
}

void ForkASTrgShootArrowWithBaseBone::calc_() {
    ForkASTrgShootArrow::calc_();
}

}  // namespace uking::action
