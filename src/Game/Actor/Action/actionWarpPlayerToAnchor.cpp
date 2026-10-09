#include "Game/Actor/Action/actionWarpPlayerToAnchor.h"

namespace uking::action {

WarpPlayerToAnchor::WarpPlayerToAnchor(const InitArg& arg) : DestPlayerWarpBase(arg) {}

WarpPlayerToAnchor::~WarpPlayerToAnchor() = default;

bool WarpPlayerToAnchor::init_(sead::Heap* heap) {
    return DestPlayerWarpBase::init_(heap);
}

void WarpPlayerToAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    DestPlayerWarpBase::enter_(params);
}

void WarpPlayerToAnchor::leave_() {
    DestPlayerWarpBase::leave_();
}

void WarpPlayerToAnchor::loadParams_() {
    DestPlayerWarpBase::loadParams_();
    getDynamicParam(&mUniqueName_d, "UniqueName");
    getDynamicParam(&mAnchorName_d, "AnchorName");
}

void WarpPlayerToAnchor::calc_() {
    DestPlayerWarpBase::calc_();
}

}  // namespace uking::action
