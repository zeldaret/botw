#include "Game/AI/Action/actionFreezedInIce.h"

namespace uking::action {

FreezedInIce::FreezedInIce(const InitArg& arg) : ksys::act::ai::Action(arg) {}

bool FreezedInIce::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FreezedInIce::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FreezedInIce::leave_() {
    ksys::act::ai::Action::leave_();
}

void FreezedInIce::loadParams_() {}

void FreezedInIce::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
