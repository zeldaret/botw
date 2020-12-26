#include "Game/AI/Action/actionWarpPlayerToAnchorGimmickReset.h"

namespace uking::action {

WarpPlayerToAnchorGimmickReset::WarpPlayerToAnchorGimmickReset(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

WarpPlayerToAnchorGimmickReset::~WarpPlayerToAnchorGimmickReset() = default;

bool WarpPlayerToAnchorGimmickReset::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpPlayerToAnchorGimmickReset::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpPlayerToAnchorGimmickReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpPlayerToAnchorGimmickReset::loadParams_() {
    getStaticParam(&mWaitFrameAfterReset_s, "WaitFrameAfterReset");
    getMapUnitParam(&mAnchorName_m, "AnchorName");
    getMapUnitParam(&mAnchorUniqueName_m, "AnchorUniqueName");
}

void WarpPlayerToAnchorGimmickReset::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
