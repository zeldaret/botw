#include "Game/AI/Action/actionChangeScheduleAnchor.h"

namespace uking::action {

ChangeScheduleAnchor::ChangeScheduleAnchor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeScheduleAnchor::~ChangeScheduleAnchor() = default;

bool ChangeScheduleAnchor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeScheduleAnchor::loadParams_() {
    getDynamicParam(&mScheduleName_d, "ScheduleName");
    getDynamicParam(&mAnchorUniqueName_d, "AnchorUniqueName");
}

}  // namespace uking::action
