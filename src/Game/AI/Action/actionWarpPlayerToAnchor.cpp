#include "Game/AI/Action/actionWarpPlayerToAnchor.h"

namespace uking::action {

WarpPlayerToAnchor::WarpPlayerToAnchor(const InitArg& arg) : WarpPlayerBase(arg) {}

WarpPlayerToAnchor::~WarpPlayerToAnchor() = default;

bool WarpPlayerToAnchor::init_(sead::Heap* heap) {
    return WarpPlayerBase::init_(heap);
}

void WarpPlayerToAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    WarpPlayerBase::enter_(params);
}

void WarpPlayerToAnchor::leave_() {
    WarpPlayerBase::leave_();
}

void WarpPlayerToAnchor::loadParams_() {
    WarpPlayerBase::loadParams_();
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

void WarpPlayerToAnchor::calc_() {
    WarpPlayerBase::calc_();
}

}  // namespace uking::action
