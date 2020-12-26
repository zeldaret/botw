#include "Game/AI/Action/actionWarpToDynamicPos.h"

namespace uking::action {

WarpToDynamicPos::WarpToDynamicPos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToDynamicPos::~WarpToDynamicPos() = default;

bool WarpToDynamicPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToDynamicPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpToDynamicPos::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpToDynamicPos::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetFoward_d, "TargetFoward");
}

void WarpToDynamicPos::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
