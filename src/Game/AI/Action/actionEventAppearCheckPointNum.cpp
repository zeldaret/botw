#include "Game/AI/Action/actionEventAppearCheckPointNum.h"

namespace uking::action {

EventAppearCheckPointNum::EventAppearCheckPointNum(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventAppearCheckPointNum::~EventAppearCheckPointNum() = default;

bool EventAppearCheckPointNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAppearCheckPointNum::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventAppearCheckPointNum::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAppearCheckPointNum::loadParams_() {
    getDynamicParam(&mIconType_d, "IconType");
    getDynamicParam(&mGameDataIntTargetCounter_d, "GameDataIntTargetCounter");
}

void EventAppearCheckPointNum::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
