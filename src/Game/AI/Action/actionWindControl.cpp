#include "Game/AI/Action/actionWindControl.h"

namespace uking::action {

WindControl::WindControl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WindControl::~WindControl() = default;

bool WindControl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WindControl::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WindControl::leave_() {
    ksys::act::ai::Action::leave_();
}

void WindControl::loadParams_() {
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mMaxSpeed_s, "MaxSpeed");
    getStaticParam(&mMaxRadSpeed_s, "MaxRadSpeed");
    getStaticParam(&mRadAccel_s, "RadAccel");
    getStaticParam(&mTemperature_s, "Temperature");
    getStaticParam(&mUseEnvTemperature_s, "UseEnvTemperature");
    getStaticParam(&mIsModelControlOnly_s, "IsModelControlOnly");
    getStaticParam(&mTargetNodeName_s, "TargetNodeName");
}

void WindControl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
