#include "Game/AI/Action/actionDemoVoiceTrigger.h"

namespace uking::action {

DemoVoiceTrigger::DemoVoiceTrigger(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoVoiceTrigger::~DemoVoiceTrigger() = default;

bool DemoVoiceTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoVoiceTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoVoiceTrigger::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoVoiceTrigger::loadParams_() {
    getDynamicParam(&mIsHideCaption_d, "IsHideCaption");
    getDynamicParam(&mLabel_d, "Label");
    getDynamicParam(&mActorInstance_d, "ActorInstance");
}

void DemoVoiceTrigger::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
