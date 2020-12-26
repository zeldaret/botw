#include "Game/AI/Action/actionSwitchWindmill.h"

namespace uking::action {

SwitchWindmill::SwitchWindmill(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SwitchWindmill::~SwitchWindmill() = default;

bool SwitchWindmill::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SwitchWindmill::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SwitchWindmill::leave_() {
    ksys::act::ai::Action::leave_();
}

void SwitchWindmill::loadParams_() {
    getStaticParam(&mSwRadTh_s, "SwRadTh");
    getStaticParam(&mSwRadAllowance_s, "SwRadAllowance");
    getStaticParam(&mRotAccel_s, "RotAccel");
    getStaticParam(&mMaxRotSpeed_s, "MaxRotSpeed");
    getStaticParam(&mTargetNodeName_s, "TargetNodeName");
}

void SwitchWindmill::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
