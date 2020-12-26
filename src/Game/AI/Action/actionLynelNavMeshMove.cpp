#include "Game/AI/Action/actionLynelNavMeshMove.h"

namespace uking::action {

LynelNavMeshMove::LynelNavMeshMove(const InitArg& arg) : AnimalMoveGuidedBase(arg) {}

LynelNavMeshMove::~LynelNavMeshMove() = default;

bool LynelNavMeshMove::init_(sead::Heap* heap) {
    return AnimalMoveGuidedBase::init_(heap);
}

void LynelNavMeshMove::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveGuidedBase::enter_(params);
}

void LynelNavMeshMove::leave_() {
    AnimalMoveGuidedBase::leave_();
}

void LynelNavMeshMove::loadParams_() {
    AnimalMoveGuidedBase::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
    // FIXME: CALL sub_710070F984 @ 0x710070f984
}

void LynelNavMeshMove::calc_() {
    AnimalMoveGuidedBase::calc_();
}

}  // namespace uking::action
