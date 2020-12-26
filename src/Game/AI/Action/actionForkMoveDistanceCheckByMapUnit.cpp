#include "Game/AI/Action/actionForkMoveDistanceCheckByMapUnit.h"

namespace uking::action {

ForkMoveDistanceCheckByMapUnit::ForkMoveDistanceCheckByMapUnit(const InitArg& arg)
    : ForkMoveDistanceCheckByDistance(arg) {}

ForkMoveDistanceCheckByMapUnit::~ForkMoveDistanceCheckByMapUnit() = default;

bool ForkMoveDistanceCheckByMapUnit::init_(sead::Heap* heap) {
    return ForkMoveDistanceCheckByDistance::init_(heap);
}

void ForkMoveDistanceCheckByMapUnit::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkMoveDistanceCheckByDistance::enter_(params);
}

void ForkMoveDistanceCheckByMapUnit::leave_() {
    ForkMoveDistanceCheckByDistance::leave_();
}

void ForkMoveDistanceCheckByMapUnit::loadParams_() {
    ForkMoveDistanceCheckByDistance::loadParams_();
    getMapUnitParam(&mRange_m, "Range");
}

void ForkMoveDistanceCheckByMapUnit::calc_() {
    ForkMoveDistanceCheckByDistance::calc_();
}

}  // namespace uking::action
