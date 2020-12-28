#include "Game/AI/Action/actionEventAppearCheckPointNum.h"

namespace uking::action {

EventAppearCheckPointNum::EventAppearCheckPointNum(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventAppearCheckPointNum::~EventAppearCheckPointNum() = default;

bool EventAppearCheckPointNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAppearCheckPointNum::loadParams_() {
    getDynamicParam(&mIconType_d, "IconType");
    getDynamicParam(&mGameDataIntTargetCounter_d, "GameDataIntTargetCounter");
}

}  // namespace uking::action
