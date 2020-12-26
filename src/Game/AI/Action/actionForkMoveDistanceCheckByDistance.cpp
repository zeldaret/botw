#include "Game/AI/Action/actionForkMoveDistanceCheckByDistance.h"

namespace uking::action {

ForkMoveDistanceCheckByDistance::ForkMoveDistanceCheckByDistance(const InitArg& arg) : Fork(arg) {}

ForkMoveDistanceCheckByDistance::~ForkMoveDistanceCheckByDistance() = default;

bool ForkMoveDistanceCheckByDistance::init_(sead::Heap* heap) {
    return Fork::init_(heap);
}

void ForkMoveDistanceCheckByDistance::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork::enter_(params);
}

void ForkMoveDistanceCheckByDistance::leave_() {
    Fork::leave_();
}

void ForkMoveDistanceCheckByDistance::loadParams_() {
    Fork::loadParams_();
    getStaticParam(&mIsCheckOnlyXZ_s, "IsCheckOnlyXZ");
}

void ForkMoveDistanceCheckByDistance::calc_() {
    Fork::calc_();
}

}  // namespace uking::action
