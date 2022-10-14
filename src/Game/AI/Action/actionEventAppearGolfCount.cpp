#include "Game/AI/Action/actionEventAppearGolfCount.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

EventAppearGolfCount::EventAppearGolfCount(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventAppearGolfCount::~EventAppearGolfCount() = default;

bool EventAppearGolfCount::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventAppearGolfCount::oneShot_() {
    ui::setShowGolfCount(mGameDataIntTargetCounter_d);
    return ksys::act::ai::Action::oneShot_();
}

void EventAppearGolfCount::loadParams_() {
    getDynamicParam(&mGameDataIntTargetCounter_d, "GameDataIntTargetCounter");
}

}  // namespace uking::action
