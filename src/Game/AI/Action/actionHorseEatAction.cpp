#include "Game/AI/Action/actionHorseEatAction.h"

namespace uking::action {

HorseEatAction::HorseEatAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseEatAction::~HorseEatAction() = default;

bool HorseEatAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseEatAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseEatAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseEatAction::loadParams_() {
    getStaticParam(&mTargetDirToStickX_s, "TargetDirToStickX");
    getStaticParam(&mTargetDistOffset_s, "TargetDistOffset");
    getStaticParam(&mTargetDistToStickY_s, "TargetDistToStickY");
    getStaticParam(&mMaxStickXForEat_s, "MaxStickXForEat");
    getStaticParam(&mMaxStickYForEat_s, "MaxStickYForEat");
    getStaticParam(&mDelayFrames_s, "DelayFrames");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void HorseEatAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
