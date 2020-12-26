#include "Game/AI/Action/actionForkAlwaysOneColTgOff.h"

namespace uking::action {

ForkAlwaysOneColTgOff::ForkAlwaysOneColTgOff(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAlwaysOneColTgOff::~ForkAlwaysOneColTgOff() = default;

bool ForkAlwaysOneColTgOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysOneColTgOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAlwaysOneColTgOff::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAlwaysOneColTgOff::loadParams_() {
    getStaticParam(&mRigidBodyName_s, "RigidBodyName");
}

void ForkAlwaysOneColTgOff::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
