#include "Game/AI/Action/actionWaitForASTriggerEvent.h"

namespace uking::action {

WaitForASTriggerEvent::WaitForASTriggerEvent(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WaitForASTriggerEvent::~WaitForASTriggerEvent() = default;

bool WaitForASTriggerEvent::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WaitForASTriggerEvent::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WaitForASTriggerEvent::leave_() {
    ksys::act::ai::Action::leave_();
}

void WaitForASTriggerEvent::loadParams_() {
    getDynamicParam(&mEventType_d, "EventType");
    getDynamicParam(&mActorName_d, "ActorName");
    getDynamicParam(&mUniqueName_d, "UniqueName");
}

void WaitForASTriggerEvent::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
