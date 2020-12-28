#include "Game/AI/Action/actionHorseMoveToTargetAction.h"

namespace uking::action {

HorseMoveToTargetAction::HorseMoveToTargetAction(const InitArg& arg) : AnimalMoveGuidedBase(arg) {}

bool HorseMoveToTargetAction::init_(sead::Heap* heap) {
    return AnimalMoveGuidedBase::init_(heap);
}

void HorseMoveToTargetAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveGuidedBase::enter_(params);
}

void HorseMoveToTargetAction::leave_() {
    AnimalMoveGuidedBase::leave_();
}

void HorseMoveToTargetAction::loadParams_() {
    AnimalMoveGuidedBase::loadParams_();
    getStaticParam(&mIsCancelRequestedPathFirst_s, "IsCancelRequestedPathFirst");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void HorseMoveToTargetAction::calc_() {
    AnimalMoveGuidedBase::calc_();
}

}  // namespace uking::action
