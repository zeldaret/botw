#include "Game/AI/Action/actionCustomDuckingStartAction.h"

namespace uking::action {

CustomDuckingStartAction::CustomDuckingStartAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CustomDuckingStartAction::~CustomDuckingStartAction() = default;

bool CustomDuckingStartAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CustomDuckingStartAction::loadParams_() {
    getDynamicParam(&mVolume_d, "Volume");
    getDynamicParam(&mFadeOutSec_d, "FadeOutSec");
    getDynamicParam(&mFadeInSec_d, "FadeInSec");
    getDynamicParam(&mStartDelaySec_d, "StartDelaySec");
    getDynamicParam(&mTargetGroups_d, "TargetGroups");
    getDynamicParam(&mExceptGroups_d, "ExceptGroups");
}

}  // namespace uking::action
