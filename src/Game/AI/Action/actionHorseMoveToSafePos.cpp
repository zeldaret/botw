#include "Game/AI/Action/actionHorseMoveToSafePos.h"

namespace uking::action {

HorseMoveToSafePos::HorseMoveToSafePos(const InitArg& arg) : AnimalMoveGuidedBase(arg) {}

HorseMoveToSafePos::~HorseMoveToSafePos() = default;

bool HorseMoveToSafePos::init_(sead::Heap* heap) {
    return AnimalMoveGuidedBase::init_(heap);
}

void HorseMoveToSafePos::enter_(ksys::act::ai::InlineParamPack* params) {
    AnimalMoveGuidedBase::enter_(params);
}

void HorseMoveToSafePos::leave_() {
    AnimalMoveGuidedBase::leave_();
}

void HorseMoveToSafePos::loadParams_() {
    AnimalMoveGuidedBase::loadParams_();
    getStaticParam(&mSearchRadius_s, "SearchRadius");
    getStaticParam(&mAreaThreshold_s, "AreaThreshold");
    getStaticParam(&mResolvePenetrationRadiusScale_s, "ResolvePenetrationRadiusScale");
    getStaticParam(&mResolvePenetrationSearchRadius_s, "ResolvePenetrationSearchRadius");
    getStaticParam(&mSetEndIfCurrentFaceIsSafe_s, "SetEndIfCurrentFaceIsSafe");
}

void HorseMoveToSafePos::calc_() {
    AnimalMoveGuidedBase::calc_();
}

}  // namespace uking::action
