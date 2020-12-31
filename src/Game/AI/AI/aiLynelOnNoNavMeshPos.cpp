#include "Game/AI/AI/aiLynelOnNoNavMeshPos.h"

namespace uking::ai {

LynelOnNoNavMeshPos::LynelOnNoNavMeshPos(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelOnNoNavMeshPos::~LynelOnNoNavMeshPos() = default;

bool LynelOnNoNavMeshPos::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelOnNoNavMeshPos::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelOnNoNavMeshPos::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelOnNoNavMeshPos::loadParams_() {
    getStaticParam(&mJumpTimer_s, "JumpTimer");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mHeavySlopeAngle_s, "HeavySlopeAngle");
    getStaticParam(&mNoJumpDist_s, "NoJumpDist");
    getStaticParam(&mHyperJumpDist_s, "HyperJumpDist");
}

}  // namespace uking::ai
