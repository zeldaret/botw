#include "Game/AI/Action/actionEventResetQuestAction.h"

namespace uking::action {

EventResetQuestAction::EventResetQuestAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventResetQuestAction::~EventResetQuestAction() = default;

bool EventResetQuestAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventResetQuestAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventResetQuestAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventResetQuestAction::loadParams_() {
    getDynamicParam(&mQuestName_d, "QuestName");
}

void EventResetQuestAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
