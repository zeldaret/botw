#include "Game/AI/Action/actionRegistedActorBroadCastMessage.h"

namespace uking::action {

RegistedActorBroadCastMessage::RegistedActorBroadCastMessage(const InitArg& arg)
    : RegistedActorActionBase(arg) {}

RegistedActorBroadCastMessage::~RegistedActorBroadCastMessage() = default;

bool RegistedActorBroadCastMessage::init_(sead::Heap* heap) {
    return RegistedActorActionBase::init_(heap);
}

void RegistedActorBroadCastMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorActionBase::enter_(params);
}

void RegistedActorBroadCastMessage::leave_() {
    RegistedActorActionBase::leave_();
}

void RegistedActorBroadCastMessage::loadParams_() {
    RegistedActorActionBase::loadParams_();
}

void RegistedActorBroadCastMessage::calc_() {
    RegistedActorActionBase::calc_();
}

}  // namespace uking::action
