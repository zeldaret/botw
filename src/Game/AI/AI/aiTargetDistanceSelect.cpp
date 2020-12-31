#include "Game/AI/AI/aiTargetDistanceSelect.h"

namespace uking::ai {

TargetDistanceSelect::TargetDistanceSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetDistanceSelect::~TargetDistanceSelect() = default;

bool TargetDistanceSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetDistanceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetDistanceSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetDistanceSelect::loadParams_() {
    getStaticParam(&mBoundaryDistance_s, "BoundaryDistance");
    getStaticParam(&mOverlapDistance_s, "OverlapDistance");
    getStaticParam(&mIsUpdateTarget_s, "IsUpdateTarget");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
