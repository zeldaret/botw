#include "Game/AI/Action/actionEventOpenMessageTips.h"

namespace uking::action {

EventOpenMessageTips::EventOpenMessageTips(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventOpenMessageTips::~EventOpenMessageTips() = default;

bool EventOpenMessageTips::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventOpenMessageTips::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventOpenMessageTips::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventOpenMessageTips::loadParams_() {
    getDynamicParam(&mTipsType_d, "TipsType");
    getDynamicParam(&mMessageId_d, "MessageId");
}

void EventOpenMessageTips::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
