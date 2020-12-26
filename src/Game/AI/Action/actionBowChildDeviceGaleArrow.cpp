#include "Game/AI/Action/actionBowChildDeviceGaleArrow.h"

namespace uking::action {

BowChildDeviceGaleArrow::BowChildDeviceGaleArrow(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildDeviceGaleArrow::~BowChildDeviceGaleArrow() = default;

bool BowChildDeviceGaleArrow::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildDeviceGaleArrow::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BowChildDeviceGaleArrow::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildDeviceGaleArrow::loadParams_() {
    getStaticParam(&mMaxMoveSpeed_s, "MaxMoveSpeed");
    getStaticParam(&mRotateSpeedMax_s, "RotateSpeedMax");
    getStaticParam(&mRotateAccel_s, "RotateAccel");
    getStaticParam(&mRotateOffset_s, "RotateOffset");
    getStaticParam(&mCenterOffset_s, "CenterOffset");
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mXRotateAngle_d, "XRotateAngle");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

void BowChildDeviceGaleArrow::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
