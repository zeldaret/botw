#include "Game/AI/AI/aiMessageReceiveCheckEveryFrame.h"

namespace uking::ai {

MessageReceiveCheckEveryFrame::MessageReceiveCheckEveryFrame(const InitArg& arg)
    : MessageReceiveCheckBasic(arg) {}

MessageReceiveCheckEveryFrame::~MessageReceiveCheckEveryFrame() = default;

bool MessageReceiveCheckEveryFrame::init_(sead::Heap* heap) {
    return MessageReceiveCheckBasic::init_(heap);
}

void MessageReceiveCheckEveryFrame::enter_(ksys::act::ai::InlineParamPack* params) {
    MessageReceiveCheckBasic::enter_(params);
}

void MessageReceiveCheckEveryFrame::leave_() {
    MessageReceiveCheckBasic::leave_();
}

void MessageReceiveCheckEveryFrame::loadParams_() {
    MessageReceiveCheckBasic::loadParams_();
    getStaticParam(&mMsgType_s, "MsgType");
}

}  // namespace uking::ai
