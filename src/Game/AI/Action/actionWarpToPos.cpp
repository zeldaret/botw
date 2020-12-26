#include "Game/AI/Action/actionWarpToPos.h"

namespace uking::action {

WarpToPos::WarpToPos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpToPos::~WarpToPos() = default;

bool WarpToPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpToPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpToPos::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpToPos::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetRot_d, "TargetRot");
}

void WarpToPos::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
