#include "Game/AI/Action/actionHorseRandomMoveAction.h"

namespace uking::action {

HorseRandomMoveAction::HorseRandomMoveAction(const InitArg& arg) : AnimalMoveGuidedBase(arg) {}

void HorseRandomMoveAction::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveGuidedBase::enter_(params);
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

}  // namespace uking::action
