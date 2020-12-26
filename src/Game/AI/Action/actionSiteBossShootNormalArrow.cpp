#include "Game/AI/Action/actionSiteBossShootNormalArrow.h"

namespace uking::action {

SiteBossShootNormalArrow::SiteBossShootNormalArrow(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossShootNormalArrow::~SiteBossShootNormalArrow() = default;

bool SiteBossShootNormalArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossShootNormalArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SiteBossShootNormalArrow::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossShootNormalArrow::loadParams_() {
    getStaticParam(&mInitSpeed_s, "InitSpeed");
    getStaticParam(&mTargetOffsetY_s, "TargetOffsetY");
    getStaticParam(&mIsConnectChild_s, "IsConnectChild");
    getStaticParam(&mIsCheckASEvent_s, "IsCheckASEvent");
    getStaticParam(&mIsTurnToTarget_s, "IsTurnToTarget");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mDirMinAngle_s, "DirMinAngle");
    getStaticParam(&mDirMaxAngle_s, "DirMaxAngle");
    getDynamicParam(&mIndex_d, "Index");
    getDynamicParam(&mAtAttr_d, "AtAttr");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIgniteActor_d, "IgniteActor");
    getDynamicParam(&mArrowHandle_d, "ArrowHandle");
}

void SiteBossShootNormalArrow::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
