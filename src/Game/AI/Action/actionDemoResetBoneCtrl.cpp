#include "Game/AI/Action/actionDemoResetBoneCtrl.h"

namespace uking::action {

DemoResetBoneCtrl::DemoResetBoneCtrl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoResetBoneCtrl::~DemoResetBoneCtrl() = default;

bool DemoResetBoneCtrl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoResetBoneCtrl::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoResetBoneCtrl::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoResetBoneCtrl::loadParams_() {
    getDynamicParam(&mResetTarget_d, "ResetTarget");
}

void DemoResetBoneCtrl::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
