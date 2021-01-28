#include "Game/AI/Action/actionSendMessage.h"

namespace uking::action {

SendMessage::SendMessage(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SendMessage::~SendMessage() = default;

bool SendMessage::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SendMessage::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    if (*mSendTiming_s == 0)
        doSendMessage();

    mFlags.set(Flag::_4);
    setFinished();
}

void SendMessage::leave_() {
    ksys::act::ai::Action::leave_();
    if (*mSendTiming_s == 1)
        doSendMessage();
}

void SendMessage::loadParams_() {
    getStaticParam(&mSendTiming_s, "SendTiming");
}

void SendMessage::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
