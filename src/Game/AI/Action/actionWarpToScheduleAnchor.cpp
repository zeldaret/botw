#include "Game/AI/Action/actionWarpToScheduleAnchor.h"

namespace uking::action {

WarpToScheduleAnchor::WarpToScheduleAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToScheduleAnchor::~WarpToScheduleAnchor() = default;

bool WarpToScheduleAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToScheduleAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpToScheduleAnchor::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpToScheduleAnchor::loadParams_() {
    getDynamicParam(&mAnchorName_d, "AnchorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void WarpToScheduleAnchor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
