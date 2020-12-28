#include "Game/AI/Action/actionEventRollbackQuestAction.h"

namespace uking::action {

EventRollbackQuestAction::EventRollbackQuestAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventRollbackQuestAction::~EventRollbackQuestAction() = default;

bool EventRollbackQuestAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventRollbackQuestAction::loadParams_() {
    getDynamicParam(&mQuestName_d, "QuestName");
    getDynamicParam(&mStepName_d, "StepName");
}

}  // namespace uking::action
