#include "Game/AI/Action/actionActorAreaInOutSendMessage.h"

namespace uking::action {

ActorAreaInOutSendMessage::ActorAreaInOutSendMessage(const InitArg& arg) : AreaTagAction(arg) {}

ActorAreaInOutSendMessage::~ActorAreaInOutSendMessage() = default;

bool ActorAreaInOutSendMessage::init_(sead::Heap* heap) {
    return AreaTagAction::init_(heap);
}

void ActorAreaInOutSendMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaTagAction::enter_(params);
}

void ActorAreaInOutSendMessage::leave_() {
    AreaTagAction::leave_();
}

void ActorAreaInOutSendMessage::loadParams_() {
    getStaticParam(&mBufferNum_s, "BufferNum");
}

void ActorAreaInOutSendMessage::calc_() {
    AreaTagAction::calc_();
}

}  // namespace uking::action
