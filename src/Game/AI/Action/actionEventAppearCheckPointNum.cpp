#include "Game/AI/Action/actionEventAppearCheckPointNum.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

EventAppearCheckPointNum::EventAppearCheckPointNum(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventAppearCheckPointNum::~EventAppearCheckPointNum() = default;

bool EventAppearCheckPointNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool EventAppearCheckPointNum::oneShot_() {
    ui::setShowCheckPoint(*mIconType_d, mGameDataIntTargetCounter_d);
    return ksys::act::ai::Action::oneShot_();
}

void EventAppearCheckPointNum::loadParams_() {
    getDynamicParam(&mIconType_d, "IconType");
    getDynamicParam(&mGameDataIntTargetCounter_d, "GameDataIntTargetCounter");
}

}  // namespace uking::action
