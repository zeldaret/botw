#include "Game/AI/Action/actionForceSetPlayerRestartPosAngle.h"

namespace uking::action {

ForceSetPlayerRestartPosAngle::ForceSetPlayerRestartPosAngle(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForceSetPlayerRestartPosAngle::~ForceSetPlayerRestartPosAngle() = default;

bool ForceSetPlayerRestartPosAngle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceSetPlayerRestartPosAngle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForceSetPlayerRestartPosAngle::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceSetPlayerRestartPosAngle::loadParams_() {
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

void ForceSetPlayerRestartPosAngle::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
