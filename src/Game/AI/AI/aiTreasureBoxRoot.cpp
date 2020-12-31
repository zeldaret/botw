#include "Game/AI/AI/aiTreasureBoxRoot.h"

namespace uking::ai {

TreasureBoxRoot::TreasureBoxRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TreasureBoxRoot::~TreasureBoxRoot() = default;

bool TreasureBoxRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TreasureBoxRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TreasureBoxRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TreasureBoxRoot::loadParams_() {
    getStaticParam(&mInGroundOffsetY_s, "InGroundOffsetY");
    getStaticParam(&mInGroundScale_s, "InGroundScale");
    getStaticParam(&mOnGroundOffsetY_s, "OnGroundOffsetY");
    getStaticParam(&mOnGroundScale_s, "OnGroundScale");
    getStaticParam(&mJumpPower_s, "JumpPower");
    getStaticParam(&mDebugDraw_s, "DebugDraw");
    getMapUnitParam(&mIsInGround_m, "IsInGround");
    getMapUnitParam(&mEnableRevival_m, "EnableRevival");
}

}  // namespace uking::ai
