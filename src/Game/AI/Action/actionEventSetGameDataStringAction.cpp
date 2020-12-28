#include "Game/AI/Action/actionEventSetGameDataStringAction.h"

namespace uking::action {

EventSetGameDataStringAction::EventSetGameDataStringAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetGameDataStringAction::~EventSetGameDataStringAction() = default;

bool EventSetGameDataStringAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetGameDataStringAction::loadParams_() {
    getDynamicParam(&mGameDataStringName_d, "GameDataStringName");
    getDynamicParam(&mValue_d, "Value");
}

}  // namespace uking::action
