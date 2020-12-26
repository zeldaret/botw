#include "Game/AI/Action/actionForkToggleFreeMoving.h"

namespace uking::action {

ForkToggleFreeMoving::ForkToggleFreeMoving(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkToggleFreeMoving::~ForkToggleFreeMoving() = default;

bool ForkToggleFreeMoving::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkToggleFreeMoving::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkToggleFreeMoving::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkToggleFreeMoving::loadParams_() {
    getStaticParam(&mEnterChoice_s, "EnterChoice");
    getStaticParam(&mLeaveChoice_s, "LeaveChoice");
}

void ForkToggleFreeMoving::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
