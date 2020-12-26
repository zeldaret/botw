#include "Game/AI/Action/actionRegistedActorActionBase.h"

namespace uking::action {

RegistedActorActionBase::RegistedActorActionBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RegistedActorActionBase::~RegistedActorActionBase() = default;

bool RegistedActorActionBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RegistedActorActionBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RegistedActorActionBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void RegistedActorActionBase::loadParams_() {
    getStaticParam(&mTeachSelfRegistedActor_s, "TeachSelfRegistedActor");
}

void RegistedActorActionBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
