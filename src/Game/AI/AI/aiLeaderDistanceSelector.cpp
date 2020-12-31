#include "Game/AI/AI/aiLeaderDistanceSelector.h"

namespace uking::ai {

LeaderDistanceSelector::LeaderDistanceSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LeaderDistanceSelector::~LeaderDistanceSelector() = default;

bool LeaderDistanceSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LeaderDistanceSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LeaderDistanceSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LeaderDistanceSelector::loadParams_() {
    getStaticParam(&mBoundaryDistance_s, "BoundaryDistance");
    getStaticParam(&mOverlapDistance_s, "OverlapDistance");
    getDynamicParam(&mLeaderActor_d, "LeaderActor");
}

}  // namespace uking::ai
