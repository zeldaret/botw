#include "Game/Actor/Action/actionAreaInOutSendMessage.h"

namespace uking::action {

AreaInOutSendMessage::AreaInOutSendMessage(const InitArg& arg) : AreaActionBase(arg) {}

AreaInOutSendMessage::~AreaInOutSendMessage() = default;

bool AreaInOutSendMessage::init_(sead::Heap* heap) {
    return AreaActionBase::init_(heap);
}

void AreaInOutSendMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    AreaActionBase::enter_(params);
}

void AreaInOutSendMessage::leave_() {
    AreaActionBase::leave_();
}

void AreaInOutSendMessage::loadParams_() {
    getStaticParam(&mBufferNum_s, "BufferNum");
}

void AreaInOutSendMessage::calc_() {
    AreaActionBase::calc_();
}

}  // namespace uking::action
