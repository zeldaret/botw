#include "Game/AI/Action/actionEventSetGameDataFloatAction.h"

namespace uking::action {

EventSetGameDataFloatAction::EventSetGameDataFloatAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetGameDataFloatAction::~EventSetGameDataFloatAction() = default;

bool EventSetGameDataFloatAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetGameDataFloatAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetGameDataFloatAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetGameDataFloatAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mGameDataFloatName_d, "GameDataFloatName");
}

void EventSetGameDataFloatAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
