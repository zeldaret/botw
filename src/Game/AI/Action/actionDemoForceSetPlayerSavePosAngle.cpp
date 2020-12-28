#include "Game/AI/Action/actionDemoForceSetPlayerSavePosAngle.h"

namespace uking::action {

DemoForceSetPlayerSavePosAngle::DemoForceSetPlayerSavePosAngle(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DemoForceSetPlayerSavePosAngle::~DemoForceSetPlayerSavePosAngle() = default;

bool DemoForceSetPlayerSavePosAngle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoForceSetPlayerSavePosAngle::loadParams_() {
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

}  // namespace uking::action
