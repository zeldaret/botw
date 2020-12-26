#include "Game/AI/Action/actionForkAlwaysRotate.h"

namespace uking::action {

ForkAlwaysRotate::ForkAlwaysRotate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAlwaysRotate::~ForkAlwaysRotate() = default;

bool ForkAlwaysRotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAlwaysRotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAlwaysRotate::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mOnEndForceStop_s, "OnEndForceStop");
    getStaticParam(&mRotAxis_s, "RotAxis");
}

void ForkAlwaysRotate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
