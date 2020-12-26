#include "Game/AI/Action/actionNPCTalkToPlayerAction.h"

namespace uking::action {

NPCTalkToPlayerAction::NPCTalkToPlayerAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTalkToPlayerAction::~NPCTalkToPlayerAction() = default;

bool NPCTalkToPlayerAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCTalkToPlayerAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTalkToPlayerAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCTalkToPlayerAction::loadParams_() {
    getDynamicParam(&mMessageId_d, "MessageId");
    getDynamicParam(&mASKeyName_d, "ASKeyName");
}

void NPCTalkToPlayerAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
