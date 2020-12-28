#include "Game/AI/Action/actionWarpToStaticAnchor.h"

namespace uking::action {

WarpToStaticAnchor::WarpToStaticAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToStaticAnchor::~WarpToStaticAnchor() = default;

bool WarpToStaticAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToStaticAnchor::loadParams_() {
    getDynamicParam(&mAnchorName_d, "AnchorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

}  // namespace uking::action
