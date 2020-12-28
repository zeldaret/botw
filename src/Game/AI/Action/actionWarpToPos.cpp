#include "Game/AI/Action/actionWarpToPos.h"

namespace uking::action {

WarpToPos::WarpToPos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToPos::~WarpToPos() = default;

bool WarpToPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToPos::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetRot_d, "TargetRot");
}

}  // namespace uking::action
