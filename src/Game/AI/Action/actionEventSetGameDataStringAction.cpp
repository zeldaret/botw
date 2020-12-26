#include "Game/AI/Action/actionEventSetGameDataStringAction.h"

namespace uking::action {

EventSetGameDataStringAction::EventSetGameDataStringAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetGameDataStringAction::~EventSetGameDataStringAction() = default;

bool EventSetGameDataStringAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetGameDataStringAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetGameDataStringAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetGameDataStringAction::loadParams_() {
    getDynamicParam(&mGameDataStringName_d, "GameDataStringName");
    getDynamicParam(&mValue_d, "Value");
}

void EventSetGameDataStringAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
