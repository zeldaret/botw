#include "Game/AI/AI/aiGuardianMiniRoot.h"

namespace uking::ai {

GuardianMiniRoot::GuardianMiniRoot(const InitArg& arg) : EnemyRoot(arg) {}

GuardianMiniRoot::~GuardianMiniRoot() = default;

bool GuardianMiniRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void GuardianMiniRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
}

void GuardianMiniRoot::leave_() {
    EnemyRoot::leave_();
}

void GuardianMiniRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mNeckRotRatio_s, "NeckRotRatio");
    getStaticParam(&mJustGuardNumForBreak_s, "JustGuardNumForBreak");
    getStaticParam(&mRotStopSpeed_s, "RotStopSpeed");
    getAITreeVariable(&mDamagedCount_a, "DamagedCount");
    getAITreeVariable(&mIsTransformedGuardianMini_a, "IsTransformedGuardianMini");
    getAITreeVariable(&mGuardianMiniChanceTimeState_a, "GuardianMiniChanceTimeState");
}

}  // namespace uking::ai
