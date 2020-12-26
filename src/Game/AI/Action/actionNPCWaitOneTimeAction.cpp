#include "Game/AI/Action/actionNPCWaitOneTimeAction.h"

namespace uking::action {

NPCWaitOneTimeAction::NPCWaitOneTimeAction(const InitArg& arg) : NPCWait(arg) {}

NPCWaitOneTimeAction::~NPCWaitOneTimeAction() = default;

bool NPCWaitOneTimeAction::init_(sead::Heap* heap) {
    return NPCWait::init_(heap);
}

void NPCWaitOneTimeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    NPCWait::enter_(params);
}

void NPCWaitOneTimeAction::leave_() {
    NPCWait::leave_();
}

void NPCWaitOneTimeAction::loadParams_() {
    getStaticParam(&mIsIgnoreSameKey_s, "IsIgnoreSameKey");
    getStaticParam(&mASName_s, "ASName");
}

void NPCWaitOneTimeAction::calc_() {
    NPCWait::calc_();
}

}  // namespace uking::action
