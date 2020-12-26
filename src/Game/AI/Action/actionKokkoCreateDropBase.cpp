#include "Game/AI/Action/actionKokkoCreateDropBase.h"

namespace uking::action {

KokkoCreateDropBase::KokkoCreateDropBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KokkoCreateDropBase::~KokkoCreateDropBase() = default;

bool KokkoCreateDropBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KokkoCreateDropBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KokkoCreateDropBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void KokkoCreateDropBase::loadParams_() {}

void KokkoCreateDropBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
