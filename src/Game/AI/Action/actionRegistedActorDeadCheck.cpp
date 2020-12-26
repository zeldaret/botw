#include "Game/AI/Action/actionRegistedActorDeadCheck.h"

namespace uking::action {

RegistedActorDeadCheck::RegistedActorDeadCheck(const InitArg& arg)
    : RegistedActorDeadCheckBase(arg) {}

RegistedActorDeadCheck::~RegistedActorDeadCheck() = default;

bool RegistedActorDeadCheck::init_(sead::Heap* heap) {
    return RegistedActorDeadCheckBase::init_(heap);
}

void RegistedActorDeadCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorDeadCheckBase::enter_(params);
}

void RegistedActorDeadCheck::leave_() {
    RegistedActorDeadCheckBase::leave_();
}

void RegistedActorDeadCheck::loadParams_() {
    RegistedActorDeadCheckBase::loadParams_();
}

void RegistedActorDeadCheck::calc_() {
    RegistedActorDeadCheckBase::calc_();
}

}  // namespace uking::action
