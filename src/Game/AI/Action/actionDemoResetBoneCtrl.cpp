#include "Game/AI/Action/actionDemoResetBoneCtrl.h"

namespace uking::action {

DemoResetBoneCtrl::DemoResetBoneCtrl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoResetBoneCtrl::~DemoResetBoneCtrl() = default;

bool DemoResetBoneCtrl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoResetBoneCtrl::loadParams_() {
    getDynamicParam(&mResetTarget_d, "ResetTarget");
}

}  // namespace uking::action
