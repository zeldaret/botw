#include "Game/AI/Action/actionEventResetQuestAction.h"

namespace uking::action {

EventResetQuestAction::EventResetQuestAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventResetQuestAction::~EventResetQuestAction() = default;

bool EventResetQuestAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventResetQuestAction::loadParams_() {
    getDynamicParam(&mQuestName_d, "QuestName");
}

}  // namespace uking::action
