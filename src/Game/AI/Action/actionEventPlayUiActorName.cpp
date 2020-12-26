#include "Game/AI/Action/actionEventPlayUiActorName.h"

namespace uking::action {

EventPlayUiActorName::EventPlayUiActorName(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiActorName::~EventPlayUiActorName() = default;

bool EventPlayUiActorName::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiActorName::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayUiActorName::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPlayUiActorName::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mActorType_d, "ActorType");
    getDynamicParam(&mActorName_d, "ActorName");
}

void EventPlayUiActorName::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
