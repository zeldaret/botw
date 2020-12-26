#include "Game/AI/Action/actionForkFixedAngleVacuumShootTarget.h"

namespace uking::action {

ForkFixedAngleVacuumShootTarget::ForkFixedAngleVacuumShootTarget(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkFixedAngleVacuumShootTarget::~ForkFixedAngleVacuumShootTarget() = default;

bool ForkFixedAngleVacuumShootTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkFixedAngleVacuumShootTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkFixedAngleVacuumShootTarget::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkFixedAngleVacuumShootTarget::loadParams_() {
    getStaticParam(&mShootSpeedMin_s, "ShootSpeedMin");
    getStaticParam(&mShootSpeedMax_s, "ShootSpeedMax");
    getStaticParam(&mAngle_s, "Angle");
    getStaticParam(&mMaxNoiseDist_s, "MaxNoiseDist");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getStaticParam(&mIsReuseBullet_s, "IsReuseBullet");
    getStaticParam(&mBaseNode_s, "BaseNode");
    getStaticParam(&mPartsKey_s, "PartsKey");
    getStaticParam(&mShootOffset_s, "ShootOffset");
    getStaticParam(&mShootRotate_s, "ShootRotate");
    getStaticParam(&mShootRotSpeed_s, "ShootRotSpeed");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void ForkFixedAngleVacuumShootTarget::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
