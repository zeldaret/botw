#include "Game/AI/Action/actionHorseWaitAction.h"

namespace uking::action {

HorseWaitAction::HorseWaitAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseWaitAction::~HorseWaitAction() = default;

bool HorseWaitAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseWaitAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseWaitAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseWaitAction::loadParams_() {
    getStaticParam(&mUseGearType_s, "UseGearType");
    getStaticParam(&mSmoothStopFrames_s, "SmoothStopFrames");
    getStaticParam(&mSmoothStopFramesGear3_s, "SmoothStopFramesGear3");
    getStaticParam(&mMinFramesGear1_s, "MinFramesGear1");
    getStaticParam(&mIsCourbetteEnabled_s, "IsCourbetteEnabled");
    getStaticParam(&mIsLight_s, "IsLight");
}

void HorseWaitAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
