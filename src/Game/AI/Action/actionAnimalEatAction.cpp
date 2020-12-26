#include "Game/AI/Action/actionAnimalEatAction.h"

namespace uking::action {

AnimalEatAction::AnimalEatAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnimalEatAction::~AnimalEatAction() = default;

bool AnimalEatAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnimalEatAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnimalEatAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnimalEatAction::loadParams_() {
    getStaticParam(&mMinFramesPlayWaitAS_s, "MinFramesPlayWaitAS");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void AnimalEatAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
