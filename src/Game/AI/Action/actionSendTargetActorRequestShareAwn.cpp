#include "Game/AI/Action/actionSendTargetActorRequestShareAwn.h"

namespace uking::action {

SendTargetActorRequestShareAwn::SendTargetActorRequestShareAwn(const InitArg& arg)
    : SendMessageToTargetActor(arg) {}

SendTargetActorRequestShareAwn::~SendTargetActorRequestShareAwn() = default;

bool SendTargetActorRequestShareAwn::init_(sead::Heap* heap) {
    return SendMessageToTargetActor::init_(heap);
}

void SendTargetActorRequestShareAwn::enter_(ksys::act::ai::InlineParamPack* params) {
    SendMessageToTargetActor::enter_(params);
}

void SendTargetActorRequestShareAwn::leave_() {
    SendMessageToTargetActor::leave_();
}

void SendTargetActorRequestShareAwn::loadParams_() {
    SendMessageToTargetActor::loadParams_();
}

void SendTargetActorRequestShareAwn::calc_() {
    SendMessageToTargetActor::calc_();
}

}  // namespace uking::action
