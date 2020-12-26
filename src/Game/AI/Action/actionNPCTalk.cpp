#include "Game/AI/Action/actionNPCTalk.h"

namespace uking::action {

NPCTalk::NPCTalk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCTalk::~NPCTalk() = default;

bool NPCTalk::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCTalk::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCTalk::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCTalk::loadParams_() {
    getStaticParam(&mIsRemainOpeningDialog_s, "IsRemainOpeningDialog");
    getStaticParam(&mMinTalkTime_s, "MinTalkTime");
    getDynamicParam(&mIsCloseMessageDialog_d, "IsCloseMessageDialog");
    getDynamicParam(&mIsBecomingSpeaker_d, "IsBecomingSpeaker");
    getDynamicParam(&mIsOverWriteLabelActorName_d, "IsOverWriteLabelActorName");
    getDynamicParam(&mMessageId_d, "MessageId");
    getDynamicParam(&mASName_d, "ASName");
}

void NPCTalk::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
