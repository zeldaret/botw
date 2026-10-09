#include "Game/Actor/Action/actionRegistedActorBroadCastMessage.h"

namespace uking::action {

RegistedActorBroadCastMessage::RegistedActorBroadCastMessage(const InitArg& arg)
    : RegistedActorSetActionBase(arg) {}

RegistedActorBroadCastMessage::~RegistedActorBroadCastMessage() = default;

bool RegistedActorBroadCastMessage::init_(sead::Heap* heap) {
    return RegistedActorSetActionBase::init_(heap);
}

void RegistedActorBroadCastMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    RegistedActorSetActionBase::enter_(params);
}

void RegistedActorBroadCastMessage::leave_() {
    RegistedActorSetActionBase::leave_();
}

void RegistedActorBroadCastMessage::loadParams_() {
    RegistedActorSetActionBase::loadParams_();
}

void RegistedActorBroadCastMessage::calc_() {
    RegistedActorSetActionBase::calc_();
}

}  // namespace uking::action
