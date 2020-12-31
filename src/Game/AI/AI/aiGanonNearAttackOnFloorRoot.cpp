#include "Game/AI/AI/aiGanonNearAttackOnFloorRoot.h"

namespace uking::ai {

GanonNearAttackOnFloorRoot::GanonNearAttackOnFloorRoot(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

GanonNearAttackOnFloorRoot::~GanonNearAttackOnFloorRoot() = default;

bool GanonNearAttackOnFloorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonNearAttackOnFloorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonNearAttackOnFloorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonNearAttackOnFloorRoot::loadParams_() {
    getStaticParam(&mNearDist_s, "NearDist");
    getDynamicParam(&mIsCounter_d, "IsCounter");
    getDynamicParam(&mIsPrevBeam_d, "IsPrevBeam");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
