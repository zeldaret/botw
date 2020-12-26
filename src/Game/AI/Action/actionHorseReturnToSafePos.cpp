#include "Game/AI/Action/actionHorseReturnToSafePos.h"

namespace uking::action {

HorseReturnToSafePos::HorseReturnToSafePos(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseReturnToSafePos::~HorseReturnToSafePos() = default;

bool HorseReturnToSafePos::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseReturnToSafePos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseReturnToSafePos::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseReturnToSafePos::loadParams_() {
    getStaticParam(&mStartFadeOutFrame_s, "StartFadeOutFrame");
    getStaticParam(&mHiddenFrames_s, "HiddenFrames");
    getStaticParam(&mASName_s, "ASName");
}

void HorseReturnToSafePos::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
