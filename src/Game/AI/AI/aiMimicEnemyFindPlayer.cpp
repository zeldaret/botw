#include "Game/AI/AI/aiMimicEnemyFindPlayer.h"

namespace uking::ai {

MimicEnemyFindPlayer::MimicEnemyFindPlayer(const InitArg& arg) : EnemyBaseFindPlayer(arg) {}

MimicEnemyFindPlayer::~MimicEnemyFindPlayer() = default;

void MimicEnemyFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBaseFindPlayer::enter_(params);
}

void MimicEnemyFindPlayer::leave_() {
    EnemyBaseFindPlayer::leave_();
}

void MimicEnemyFindPlayer::loadParams_() {
    EnemyBaseFindPlayer::loadParams_();
    getStaticParam(&mPlayerForceFindDist_s, "PlayerForceFindDist");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

}  // namespace uking::ai
