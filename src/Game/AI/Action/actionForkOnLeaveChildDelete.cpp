#include "Game/AI/Action/actionForkOnLeaveChildDelete.h"

namespace uking::action {

ForkOnLeaveChildDelete::ForkOnLeaveChildDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkOnLeaveChildDelete::~ForkOnLeaveChildDelete() = default;

bool ForkOnLeaveChildDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkOnLeaveChildDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkOnLeaveChildDelete::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkOnLeaveChildDelete::loadParams_() {
    getStaticParam(&mForceDelete_s, "ForceDelete");
}

void ForkOnLeaveChildDelete::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
