#include "Game/AI/Action/actionNPCWaitAction.h"

namespace uking::action {

NPCWaitAction::NPCWaitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCWaitAction::~NPCWaitAction() = default;

void NPCWaitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCWaitAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCWaitAction::loadParams_() {
    getStaticParam(&mIsIgnoreSameKey_s, "IsIgnoreSameKey");
    getStaticParam(&mASName_s, "ASName");
}

void NPCWaitAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
