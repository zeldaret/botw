#include "Game/AI/Action/actionAnimalNavMeshMove.h"

namespace uking::action {

AnimalNavMeshMove::AnimalNavMeshMove(const InitArg& arg) : AnimalMoveGuidedBase(arg) {}

AnimalNavMeshMove::~AnimalNavMeshMove() = default;

bool AnimalNavMeshMove::init_(sead::Heap* heap) {
    return AnimalMoveGuidedBase::init_(heap);
}

void AnimalNavMeshMove::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveGuidedBase::enter_(params);
}

void AnimalNavMeshMove::leave_() {
    AnimalMoveGuidedBase::leave_();
}

void AnimalNavMeshMove::loadParams_() {
    AnimalMoveGuidedBase::loadParams_();
}

void AnimalNavMeshMove::calc_() {
    AnimalMoveGuidedBase::calc_();
}

}  // namespace uking::action
