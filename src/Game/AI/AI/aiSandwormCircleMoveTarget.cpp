#include "Game/AI/AI/aiSandwormCircleMoveTarget.h"

namespace uking::ai {

SandwormCircleMoveTarget::SandwormCircleMoveTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormCircleMoveTarget::~SandwormCircleMoveTarget() = default;

bool SandwormCircleMoveTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormCircleMoveTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandwormCircleMoveTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormCircleMoveTarget::loadParams_() {
    getStaticParam(&mDirection_s, "Direction");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mRadiusMargin_s, "RadiusMargin");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mFrontCheckLength_s, "FrontCheckLength");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
