#include "Game/AI/Action/actionEventPlayUiStaffRollImage.h"

namespace uking::action {

EventPlayUiStaffRollImage::EventPlayUiStaffRollImage(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

EventPlayUiStaffRollImage::~EventPlayUiStaffRollImage() = default;

bool EventPlayUiStaffRollImage::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiStaffRollImage::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventPlayUiStaffRollImage::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPlayUiStaffRollImage::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
    getDynamicParam(&mStartIdx_d, "StartIdx");
    getDynamicParam(&mEndIdx_d, "EndIdx");
}

void EventPlayUiStaffRollImage::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
