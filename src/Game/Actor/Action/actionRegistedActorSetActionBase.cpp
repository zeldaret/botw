#include "Game/Actor/Action/actionRegistedActorSetActionBase.h"

namespace uking::action {

RegistedActorSetActionBase::RegistedActorSetActionBase(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RegistedActorSetActionBase::~RegistedActorSetActionBase() = default;

bool RegistedActorSetActionBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RegistedActorSetActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RegistedActorSetActionBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void RegistedActorSetActionBase::loadParams_() {
    getStaticParam(&mTeachSelfRegistedActor_s, "TeachSelfRegistedActor");
}

void RegistedActorSetActionBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
