#include "Game/AI/Action/actionIgniteToTarget.h"

namespace uking::action {

IgniteToTarget::IgniteToTarget(const InitArg& arg) : OnetimeStopASPlay(arg) {}

IgniteToTarget::~IgniteToTarget() = default;

bool IgniteToTarget::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void IgniteToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void IgniteToTarget::leave_() {
    OnetimeStopASPlay::leave_();
}

void IgniteToTarget::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mMaxNoiseDist_s, "MaxNoiseDist");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
    getStaticParam(&mBaseNode_s, "BaseNode");
}

void IgniteToTarget::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
