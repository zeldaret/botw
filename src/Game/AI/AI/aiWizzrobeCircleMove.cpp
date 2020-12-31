#include "Game/AI/AI/aiWizzrobeCircleMove.h"

namespace uking::ai {

WizzrobeCircleMove::WizzrobeCircleMove(const InitArg& arg) : CircleMoveTarget(arg) {}

WizzrobeCircleMove::~WizzrobeCircleMove() = default;

bool WizzrobeCircleMove::init_(sead::Heap* heap) {
    return CircleMoveTarget::init_(heap);
}

void WizzrobeCircleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    CircleMoveTarget::enter_(params);
}

void WizzrobeCircleMove::leave_() {
    CircleMoveTarget::leave_();
}

void WizzrobeCircleMove::loadParams_() {
    CircleMoveTarget::loadParams_();
    getStaticParam(&mFinRadius_s, "FinRadius");
    getStaticParam(&mRadiusTimer_s, "RadiusTimer");
    getStaticParam(&mEndTimer_s, "EndTimer");
    getStaticParam(&mIsAttCentral_s, "IsAttCentral");
}

}  // namespace uking::ai
