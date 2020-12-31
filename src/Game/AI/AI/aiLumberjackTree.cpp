#include "Game/AI/AI/aiLumberjackTree.h"

namespace uking::ai {

LumberjackTree::LumberjackTree(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LumberjackTree::~LumberjackTree() = default;

bool LumberjackTree::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LumberjackTree::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LumberjackTree::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LumberjackTree::loadParams_() {
    getStaticParam(&mFallInterval_s, "FallInterval");
    getStaticParam(&mFellImpRate_s, "FellImpRate");
    getStaticParam(&mFellRotRate_s, "FellRotRate");
    getStaticParam(&mCutOffsetLower_s, "CutOffsetLower");
    getStaticParam(&mCutOffsetUpper_s, "CutOffsetUpper");
    getStaticParam(&mAlphaLower_s, "AlphaLower");
    getStaticParam(&mAlphaSpeed_s, "AlphaSpeed");
    getMapUnitParam(&mCutRate_m, "CutRate");
    getMapUnitParam(&mAngleY_m, "AngleY");
    getMapUnitParam(&mDropTable_m, "DropTable");
    getAITreeVariable(&mLumberjackType_a, "LumberjackType");
    getAITreeVariable(&mForceSetDropPos_a, "ForceSetDropPos");
    getAITreeVariable(&mMoveDirection_a, "MoveDirection");
}

}  // namespace uking::ai
