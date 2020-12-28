#include "Game/AI/Action/actionWarpToScheduleAnchor.h"

namespace uking::action {

WarpToScheduleAnchor::WarpToScheduleAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToScheduleAnchor::~WarpToScheduleAnchor() = default;

bool WarpToScheduleAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToScheduleAnchor::loadParams_() {
    getDynamicParam(&mAnchorName_d, "AnchorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

}  // namespace uking::action
