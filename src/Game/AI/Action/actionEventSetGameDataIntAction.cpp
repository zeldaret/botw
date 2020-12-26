#include "Game/AI/Action/actionEventSetGameDataIntAction.h"

namespace uking::action {

EventSetGameDataIntAction::EventSetGameDataIntAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetGameDataIntAction::~EventSetGameDataIntAction() = default;

bool EventSetGameDataIntAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetGameDataIntAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetGameDataIntAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetGameDataIntAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mGameDataIntName_d, "GameDataIntName");
}

void EventSetGameDataIntAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
