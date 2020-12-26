#include "Game/AI/Action/actionBindOff.h"

namespace uking::action {

BindOff::BindOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BindOff::~BindOff() = default;

bool BindOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BindOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BindOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void BindOff::loadParams_() {
    getAITreeVariable(&mEventBindUnit_a, "EventBindUnit");
}

void BindOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
