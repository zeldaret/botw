#include "Game/Actor/Action/actionRegistedActorDeadCheck.h"

namespace uking::action {

RegistedActorDeadCheck::RegistedActorDeadCheck(const InitArg& arg)
    : RegistedActorAllDeadCheckBase(arg) {}

RegistedActorDeadCheck::~RegistedActorDeadCheck() = default;

bool RegistedActorDeadCheck::init_(sead::Heap* heap) {
    return RegistedActorAllDeadCheckBase::init_(heap);
}

void RegistedActorDeadCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorAllDeadCheckBase::enter_(params);
}

void RegistedActorDeadCheck::leave_() {
    RegistedActorAllDeadCheckBase::leave_();
}

void RegistedActorDeadCheck::loadParams_() {
    RegistedActorAllDeadCheckBase::loadParams_();
}

void RegistedActorDeadCheck::calc_() {
    RegistedActorAllDeadCheckBase::calc_();
}

}  // namespace uking::action
