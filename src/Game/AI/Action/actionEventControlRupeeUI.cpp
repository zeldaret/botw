#include "Game/AI/Action/actionEventControlRupeeUI.h"

namespace uking::action {

EventControlRupeeUI::EventControlRupeeUI(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventControlRupeeUI::~EventControlRupeeUI() = default;

bool EventControlRupeeUI::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventControlRupeeUI::loadParams_() {
    getDynamicParam(&mTargetValue_d, "TargetValue");
    getDynamicParam(&mIsAppear_d, "IsAppear");
}

}  // namespace uking::action
