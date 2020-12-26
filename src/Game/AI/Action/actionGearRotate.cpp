#include "Game/AI/Action/actionGearRotate.h"

namespace uking::action {

GearRotate::GearRotate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GearRotate::~GearRotate() = default;

bool GearRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GearRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GearRotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void GearRotate::loadParams_() {
    getStaticParam(&mStopCheckSpdRate_s, "StopCheckSpdRate");
    getStaticParam(&mCheckSpdIdlingRate_s, "CheckSpdIdlingRate");
    getStaticParam(&mIsReverse_s, "IsReverse");
    getStaticParam(&mIsTwoWayGear_s, "IsTwoWayGear");
    getMapUnitParam(&mDgnRotDir_m, "DgnRotDir");
    getMapUnitParam(&mRotateSpeed_m, "RotateSpeed");
}

void GearRotate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
