#include "Game/AI/AI/aiNPCConfrontEnemy.h"

namespace uking::ai {

NPCConfrontEnemy::NPCConfrontEnemy(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCConfrontEnemy::~NPCConfrontEnemy() = default;

bool NPCConfrontEnemy::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCConfrontEnemy::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCConfrontEnemy::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCConfrontEnemy::loadParams_() {
    getStaticParam(&mReleaseDistance_s, "ReleaseDistance");
    getStaticParam(&mReleaseTime_s, "ReleaseTime");
    getStaticParam(&mRewardDistance_s, "RewardDistance");
    getStaticParam(&mTerrorDistAfterPlayerRescue_s, "TerrorDistAfterPlayerRescue");
    getDynamicParam(&mTerrorLevel_d, "TerrorLevel");
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsReturnFromDemo_d, "IsReturnFromDemo");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetVel_d, "TargetVel");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
}

}  // namespace uking::ai
