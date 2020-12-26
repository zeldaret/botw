#include "Game/AI/Action/actionEventChangeFadeColor.h"

namespace uking::action {

EventChangeFadeColor::EventChangeFadeColor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventChangeFadeColor::~EventChangeFadeColor() = default;

bool EventChangeFadeColor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventChangeFadeColor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventChangeFadeColor::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventChangeFadeColor::loadParams_() {
    getDynamicParam(&mFrame_d, "Frame");
    getDynamicParam(&mColor_d, "Color");
}

void EventChangeFadeColor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
