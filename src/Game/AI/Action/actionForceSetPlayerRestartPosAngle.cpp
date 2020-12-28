#include "Game/AI/Action/actionForceSetPlayerRestartPosAngle.h"

namespace uking::action {

ForceSetPlayerRestartPosAngle::ForceSetPlayerRestartPosAngle(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForceSetPlayerRestartPosAngle::~ForceSetPlayerRestartPosAngle() = default;

bool ForceSetPlayerRestartPosAngle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceSetPlayerRestartPosAngle::loadParams_() {
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

}  // namespace uking::action
