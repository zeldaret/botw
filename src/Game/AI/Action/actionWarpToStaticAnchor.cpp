#include "Game/AI/Action/actionWarpToStaticAnchor.h"

namespace uking::action {

WarpToStaticAnchor::WarpToStaticAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToStaticAnchor::~WarpToStaticAnchor() = default;

bool WarpToStaticAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToStaticAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpToStaticAnchor::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpToStaticAnchor::loadParams_() {
    getDynamicParam(&mAnchorName_d, "AnchorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void WarpToStaticAnchor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
