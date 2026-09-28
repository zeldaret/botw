#include "Game/Actor/Action/actionSendTargetActorMessageBase.h"

namespace uking::action {

SendTargetActorMessageBase::SendTargetActorMessageBase(const InitArg& arg) : SendMessage(arg) {}

SendTargetActorMessageBase::~SendTargetActorMessageBase() = default;

bool SendTargetActorMessageBase::init_(sead::Heap* heap) {
    return SendMessage::init_(heap);
}

void SendTargetActorMessageBase::enter_(ksys::act::ai::InlineParamPack* params) {
    SendMessage::enter_(params);
}

void SendTargetActorMessageBase::leave_() {
    SendMessage::leave_();
}

void SendTargetActorMessageBase::loadParams_() {
    SendMessage::loadParams_();
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void SendTargetActorMessageBase::calc_() {
    SendMessage::calc_();
}

}  // namespace uking::action
