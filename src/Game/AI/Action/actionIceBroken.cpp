#include "Game/AI/Action/actionIceBroken.h"

namespace uking::action {

IceBroken::IceBroken(const InitArg& arg) : ksys::act::ai::Action(arg) {}

IceBroken::~IceBroken() = default;

bool IceBroken::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IceBroken::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void IceBroken::leave_() {
    ksys::act::ai::Action::leave_();
}

void IceBroken::loadParams_() {}

void IceBroken::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
