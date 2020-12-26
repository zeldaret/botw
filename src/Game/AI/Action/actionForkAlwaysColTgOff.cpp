#include "Game/AI/Action/actionForkAlwaysColTgOff.h"

namespace uking::action {

ForkAlwaysColTgOff::ForkAlwaysColTgOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAlwaysColTgOff::~ForkAlwaysColTgOff() = default;

bool ForkAlwaysColTgOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysColTgOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAlwaysColTgOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAlwaysColTgOff::loadParams_() {}

void ForkAlwaysColTgOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
