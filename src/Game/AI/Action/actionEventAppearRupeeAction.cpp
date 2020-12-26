#include "Game/AI/Action/actionEventAppearRupeeAction.h"

namespace uking::action {

EventAppearRupeeAction::EventAppearRupeeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventAppearRupeeAction::~EventAppearRupeeAction() = default;

bool EventAppearRupeeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventAppearRupeeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventAppearRupeeAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventAppearRupeeAction::loadParams_() {
    getDynamicParam(&mIsVisible_d, "IsVisible");
}

void EventAppearRupeeAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
