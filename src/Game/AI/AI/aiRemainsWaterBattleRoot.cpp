#include "Game/AI/AI/aiRemainsWaterBattleRoot.h"

namespace uking::ai {

RemainsWaterBattleRoot::RemainsWaterBattleRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RemainsWaterBattleRoot::~RemainsWaterBattleRoot() = default;

bool RemainsWaterBattleRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainsWaterBattleRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void RemainsWaterBattleRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainsWaterBattleRoot::loadParams_() {
    getStaticParam(&mCallClearDemoTimer_s, "CallClearDemoTimer");
    getStaticParam(&mAfterDamageTimer_s, "AfterDamageTimer");
    getStaticParam(&mAfterPaooonTimer_s, "AfterPaooonTimer");
    getStaticParam(&mAfterHellTimer_s, "AfterHellTimer");
    getStaticParam(&mFirstBulletTimer_s, "FirstBulletTimer");
    getAITreeVariable(&mRemainsWaterBattleInfo_a, "RemainsWaterBattleInfo");
}

}  // namespace uking::ai
