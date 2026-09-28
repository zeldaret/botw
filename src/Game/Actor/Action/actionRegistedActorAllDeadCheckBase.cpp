#include "Game/Actor/Action/actionRegistedActorAllDeadCheckBase.h"

namespace uking::action {

RegistedActorAllDeadCheckBase::RegistedActorAllDeadCheckBase(const InitArg& arg)
    : RegistedActorSetActionBase(arg) {}

RegistedActorAllDeadCheckBase::~RegistedActorAllDeadCheckBase() = default;

bool RegistedActorAllDeadCheckBase::init_(sead::Heap* heap) {
    return RegistedActorSetActionBase::init_(heap);
}

void RegistedActorAllDeadCheckBase::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorSetActionBase::enter_(params);
}

void RegistedActorAllDeadCheckBase::leave_() {
    RegistedActorSetActionBase::leave_();
}

void RegistedActorAllDeadCheckBase::loadParams_() {
    RegistedActorSetActionBase::loadParams_();
}

void RegistedActorAllDeadCheckBase::calc_() {
    RegistedActorSetActionBase::calc_();
}

}  // namespace uking::action
