#include "Game/AI/Action/actionRegistedActorDeadCheckBase.h"

namespace uking::action {

RegistedActorDeadCheckBase::RegistedActorDeadCheckBase(const InitArg& arg)
    : RegistedActorActionBase(arg) {}

RegistedActorDeadCheckBase::~RegistedActorDeadCheckBase() = default;

bool RegistedActorDeadCheckBase::init_(sead::Heap* heap) {
    return RegistedActorActionBase::init_(heap);
}

void RegistedActorDeadCheckBase::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorActionBase::enter_(params);
}

void RegistedActorDeadCheckBase::leave_() {
    RegistedActorActionBase::leave_();
}

void RegistedActorDeadCheckBase::loadParams_() {
    RegistedActorActionBase::loadParams_();
}

void RegistedActorDeadCheckBase::calc_() {
    RegistedActorActionBase::calc_();
}

}  // namespace uking::action
