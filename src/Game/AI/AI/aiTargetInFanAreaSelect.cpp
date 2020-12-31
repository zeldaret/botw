#include "Game/AI/AI/aiTargetInFanAreaSelect.h"

namespace uking::ai {

TargetInFanAreaSelect::TargetInFanAreaSelect(const InitArg& arg) : TargetInAreaSelect(arg) {}

TargetInFanAreaSelect::~TargetInFanAreaSelect() = default;

bool TargetInFanAreaSelect::init_(sead::Heap* heap) {
    return TargetInAreaSelect::init_(heap);
}

void TargetInFanAreaSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetInAreaSelect::enter_(params);
}

void TargetInFanAreaSelect::leave_() {
    TargetInAreaSelect::leave_();
}

void TargetInFanAreaSelect::loadParams_() {
    TargetInAreaSelect::loadParams_();
    getStaticParam(&mNearYMax_s, "NearYMax");
    getStaticParam(&mNearYMin_s, "NearYMin");
    getStaticParam(&mFarYMax_s, "FarYMax");
    getStaticParam(&mFarYMin_s, "FarYMin");
    getStaticParam(&mXZRange_s, "XZRange");
    getStaticParam(&mAngle_s, "Angle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
