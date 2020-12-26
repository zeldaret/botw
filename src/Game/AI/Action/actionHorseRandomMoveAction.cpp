#include "Game/AI/Action/actionHorseRandomMoveAction.h"

namespace uking::action {

HorseRandomMoveAction::HorseRandomMoveAction(const InitArg& arg) : AnimalMoveGuidedBase(arg) {}

HorseRandomMoveAction::~HorseRandomMoveAction() = default;

bool HorseRandomMoveAction::init_(sead::Heap* heap) {
    return AnimalMoveGuidedBase::init_(heap);
}

void HorseRandomMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveGuidedBase::enter_(params);
}

void HorseRandomMoveAction::leave_() {
    AnimalMoveGuidedBase::leave_();
}

void HorseRandomMoveAction::loadParams_() {
    AnimalMoveGuidedBase::loadParams_();
    getStaticParam(&mRadiusLimit_s, "RadiusLimit");
    getStaticParam(&mForwardDirDistCoefficient_s, "ForwardDirDistCoefficient");
    getStaticParam(&mDirRandomValue_s, "DirRandomValue");
    getStaticParam(&mDirRangeDegree_s, "DirRangeDegree");
    getStaticParam(&mRejectDistRatioByNavMeshQuery_s, "RejectDistRatioByNavMeshQuery");
    getStaticParam(&mIsCancelRequestedPathFirst_s, "IsCancelRequestedPathFirst");
}

void HorseRandomMoveAction::calc_() {
    AnimalMoveGuidedBase::calc_();
}

}  // namespace uking::action
