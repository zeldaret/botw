#include "Game/AI/Action/actionEventIncreaseGameDataIntAction.h"

namespace uking::action {

EventIncreaseGameDataIntAction::EventIncreaseGameDataIntAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventIncreaseGameDataIntAction::~EventIncreaseGameDataIntAction() = default;

bool EventIncreaseGameDataIntAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventIncreaseGameDataIntAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventIncreaseGameDataIntAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventIncreaseGameDataIntAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mGameDataIntName_d, "GameDataIntName");
}

void EventIncreaseGameDataIntAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
