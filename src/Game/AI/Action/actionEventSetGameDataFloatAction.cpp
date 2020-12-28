#include "Game/AI/Action/actionEventSetGameDataFloatAction.h"

namespace uking::action {

EventSetGameDataFloatAction::EventSetGameDataFloatAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventSetGameDataFloatAction::~EventSetGameDataFloatAction() = default;

bool EventSetGameDataFloatAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetGameDataFloatAction::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mGameDataFloatName_d, "GameDataFloatName");
}

}  // namespace uking::action
