#include "Game/AI/AI/aiMimicEnemyNormal.h"

namespace uking::ai {

MimicEnemyNormal::MimicEnemyNormal(const InitArg& arg) : EnemyNormal(arg) {}

MimicEnemyNormal::~MimicEnemyNormal() = default;

void MimicEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void MimicEnemyNormal::leave_() {
    EnemyNormal::leave_();
}

void MimicEnemyNormal::loadParams_() {
    EnemyNormal::loadParams_();
    getStaticParam(&mPlayerForceFindDist_s, "PlayerForceFindDist");
    getStaticParam(&mRideHorseMaskPlayerFindDist_s, "RideHorseMaskPlayerFindDist");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

}  // namespace uking::ai
