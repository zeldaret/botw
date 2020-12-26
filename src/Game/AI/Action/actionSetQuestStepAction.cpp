#include "Game/AI/Action/actionSetQuestStepAction.h"

namespace uking::action {

SetQuestStepAction::SetQuestStepAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetQuestStepAction::~SetQuestStepAction() = default;

bool SetQuestStepAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetQuestStepAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetQuestStepAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetQuestStepAction::loadParams_() {
    getDynamicParam(&mForceRunTelop_d, "ForceRunTelop");
    getDynamicParam(&mQuestName_d, "QuestName");
    getDynamicParam(&mStepName_d, "StepName");
}

void SetQuestStepAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
