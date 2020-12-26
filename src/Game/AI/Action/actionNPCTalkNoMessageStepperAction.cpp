#include "Game/AI/Action/actionNPCTalkNoMessageStepperAction.h"

namespace uking::action {

NPCTalkNoMessageStepperAction::NPCTalkNoMessageStepperAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCTalkNoMessageStepperAction::~NPCTalkNoMessageStepperAction() = default;

bool NPCTalkNoMessageStepperAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCTalkNoMessageStepperAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTalkNoMessageStepperAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCTalkNoMessageStepperAction::loadParams_() {
    getDynamicParam(&mMessageId_d, "MessageId");
}

void NPCTalkNoMessageStepperAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
