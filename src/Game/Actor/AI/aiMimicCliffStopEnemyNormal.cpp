#include "Game/Actor/AI/aiMimicCliffStopEnemyNormal.h"

namespace uking::ai {

MimicCliffStopEnemyNormal::MimicCliffStopEnemyNormal(const InitArg& arg)
    : CliffStopEnemyNormal(arg) {}

MimicCliffStopEnemyNormal::~MimicCliffStopEnemyNormal() = default;

bool MimicCliffStopEnemyNormal::init_(sead::Heap* heap) {
    return CliffStopEnemyNormal::init_(heap);
}

void MimicCliffStopEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    CliffStopEnemyNormal::enter_(params);
}

void MimicCliffStopEnemyNormal::leave_() {
    CliffStopEnemyNormal::leave_();
}

void MimicCliffStopEnemyNormal::loadParams_() {
    CliffStopEnemyNormal::loadParams_();
    getStaticParam(&mJumpDistXZ_s, "JumpDistXZ");
}

}  // namespace uking::ai
