#include "Game/AI/AI/aiTrolleyRoot.h"

namespace uking::ai {

TrolleyRoot::TrolleyRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TrolleyRoot::~TrolleyRoot() = default;

bool TrolleyRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TrolleyRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TrolleyRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TrolleyRoot::loadParams_() {
    getStaticParam(&mNearGoalDist_s, "NearGoalDist");
    getStaticParam(&mNearGoalLimitSpd_s, "NearGoalLimitSpd");
    getStaticParam(&mNearGoalReduceRate_s, "NearGoalReduceRate");
}

}  // namespace uking::ai
