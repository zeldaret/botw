#include "Game/AI/Action/actionChangeScheduleAnchor.h"

namespace uking::action {

ChangeScheduleAnchor::ChangeScheduleAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeScheduleAnchor::~ChangeScheduleAnchor() = default;

bool ChangeScheduleAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeScheduleAnchor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChangeScheduleAnchor::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangeScheduleAnchor::loadParams_() {
    getDynamicParam(&mScheduleName_d, "ScheduleName");
    getDynamicParam(&mAnchorUniqueName_d, "AnchorUniqueName");
}

void ChangeScheduleAnchor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
