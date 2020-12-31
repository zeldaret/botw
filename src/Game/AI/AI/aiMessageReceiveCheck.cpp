#include "Game/AI/AI/aiMessageReceiveCheck.h"

namespace uking::ai {

MessageReceiveCheck::MessageReceiveCheck(const InitArg& arg) : MessageReceiveCheckBasic(arg) {}

MessageReceiveCheck::~MessageReceiveCheck() = default;

bool MessageReceiveCheck::init_(sead::Heap* heap) {
    return MessageReceiveCheckBasic::init_(heap);
}

void MessageReceiveCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    MessageReceiveCheckBasic::enter_(params);
}

void MessageReceiveCheck::leave_() {
    MessageReceiveCheckBasic::leave_();
}

void MessageReceiveCheck::loadParams_() {
    MessageReceiveCheckBasic::loadParams_();
    getStaticParam(&mMsgType_s, "MsgType");
}

}  // namespace uking::ai
