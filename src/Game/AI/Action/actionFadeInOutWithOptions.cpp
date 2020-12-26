#include "Game/AI/Action/actionFadeInOutWithOptions.h"

namespace uking::action {

FadeInOutWithOptions::FadeInOutWithOptions(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FadeInOutWithOptions::~FadeInOutWithOptions() = default;

bool FadeInOutWithOptions::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FadeInOutWithOptions::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FadeInOutWithOptions::leave_() {
    ksys::act::ai::Action::leave_();
}

void FadeInOutWithOptions::loadParams_() {
    getStaticParam(&mFadeType_s, "FadeType");
    getStaticParam(&mFadeStartFrame_s, "FadeStartFrame");
    getStaticParam(&mFadeFinishFrame_s, "FadeFinishFrame");
    getStaticParam(&mToggleAttention_s, "ToggleAttention");
    getStaticParam(&mToggleAwareness_s, "ToggleAwareness");
    getStaticParam(&mToggleEffects_s, "ToggleEffects");
    getStaticParam(&mToggleCollision_s, "ToggleCollision");
    getStaticParam(&mToggleHorseOptions_s, "ToggleHorseOptions");
}

void FadeInOutWithOptions::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
