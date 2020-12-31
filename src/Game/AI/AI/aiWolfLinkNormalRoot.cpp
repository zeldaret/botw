#include "Game/AI/AI/aiWolfLinkNormalRoot.h"

namespace uking::ai {

WolfLinkNormalRoot::WolfLinkNormalRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkNormalRoot::~WolfLinkNormalRoot() = default;

bool WolfLinkNormalRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkNormalRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkNormalRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkNormalRoot::loadParams_() {
    getStaticParam(&mShiekSensorLeadDistance_s, "ShiekSensorLeadDistance");
    getStaticParam(&mShiekSensorGoalTolerance_s, "ShiekSensorGoalTolerance");
    getStaticParam(&mShiekSensorTargetFowardOffset_s, "ShiekSensorTargetFowardOffset");
    getStaticParam(&mBattleAggressionRange_s, "BattleAggressionRange");
    getStaticParam(&mHowlAtEnemyRange_s, "HowlAtEnemyRange");
    getStaticParam(&mUtilityWantsToHunt_s, "UtilityWantsToHunt");
    getStaticParam(&mWarpToPlayerDistance_s, "WarpToPlayerDistance");
}

}  // namespace uking::ai
