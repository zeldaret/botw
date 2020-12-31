#include "Game/AI/AI/aiLumberjackFallenTree.h"

namespace uking::ai {

LumberjackFallenTree::LumberjackFallenTree(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LumberjackFallenTree::~LumberjackFallenTree() = default;

bool LumberjackFallenTree::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LumberjackFallenTree::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LumberjackFallenTree::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LumberjackFallenTree::loadParams_() {
    getStaticParam(&mToLogAngVel_s, "ToLogAngVel");
    getStaticParam(&mMaxCheckAng_s, "MaxCheckAng");
    getStaticParam(&mCheckDis_s, "CheckDis");
    getStaticParam(&mCheckHeightRate_s, "CheckHeightRate");
    getStaticParam(&mTerrorRegistAng_s, "TerrorRegistAng");
    getStaticParam(&mTerrorUnregistTimelimit_s, "TerrorUnregistTimelimit");
    getStaticParam(&mNoiseLevel_s, "NoiseLevel");
    getStaticParam(&mIsCheckHeight_s, "IsCheckHeight");
    getStaticParam(&mTerrorOffsetPos4Falling_s, "TerrorOffsetPos4Falling");
    getAITreeVariable(&mLumberjackType_a, "LumberjackType");
    getAITreeVariable(&mForceSetDropPos_a, "ForceSetDropPos");
    getAITreeVariable(&mMoveDirection_a, "MoveDirection");
}

}  // namespace uking::ai
