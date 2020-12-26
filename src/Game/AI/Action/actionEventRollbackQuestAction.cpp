#include "Game/AI/Action/actionEventRollbackQuestAction.h"

namespace uking::action {

EventRollbackQuestAction::EventRollbackQuestAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRollbackQuestAction::~EventRollbackQuestAction() = default;

bool EventRollbackQuestAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRollbackQuestAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventRollbackQuestAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventRollbackQuestAction::loadParams_() {
    getDynamicParam(&mQuestName_d, "QuestName");
    getDynamicParam(&mStepName_d, "StepName");
}

void EventRollbackQuestAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
