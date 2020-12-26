#include "Game/AI/Action/actionNPCTalkASyncAction.h"

namespace uking::action {

NPCTalkASyncAction::NPCTalkASyncAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTalkASyncAction::~NPCTalkASyncAction() = default;

bool NPCTalkASyncAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCTalkASyncAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTalkASyncAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCTalkASyncAction::loadParams_() {
    getDynamicParam(&mDispFrame_d, "DispFrame");
    getDynamicParam(&mIsChecked_d, "IsChecked");
    getDynamicParam(&mMessageId_d, "MessageId");
}

void NPCTalkASyncAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
