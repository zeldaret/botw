#include "Game/AI/Action/actionDemoForceSetPlayerSavePosAngle.h"

namespace uking::action {

DemoForceSetPlayerSavePosAngle::DemoForceSetPlayerSavePosAngle(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DemoForceSetPlayerSavePosAngle::~DemoForceSetPlayerSavePosAngle() = default;

bool DemoForceSetPlayerSavePosAngle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoForceSetPlayerSavePosAngle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoForceSetPlayerSavePosAngle::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoForceSetPlayerSavePosAngle::loadParams_() {
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

void DemoForceSetPlayerSavePosAngle::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
