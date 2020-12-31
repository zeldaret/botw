#include "Game/AI/AI/aiPreyLookAtTarget.h"

namespace uking::ai {

PreyLookAtTarget::PreyLookAtTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PreyLookAtTarget::~PreyLookAtTarget() = default;

bool PreyLookAtTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PreyLookAtTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PreyLookAtTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PreyLookAtTarget::loadParams_() {
    getStaticParam(&mLimitAngle_s, "LimitAngle");
    getStaticParam(&mIsUpdateViewPos_s, "IsUpdateViewPos");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
