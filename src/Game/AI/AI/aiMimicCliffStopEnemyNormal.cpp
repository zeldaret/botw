#include "Game/AI/AI/aiMimicCliffStopEnemyNormal.h"

namespace uking::ai {

MimicCliffStopEnemyNormal::MimicCliffStopEnemyNormal(const InitArg& arg)
    : MimicCliffStopEnemyNormalBase(arg) {}

MimicCliffStopEnemyNormal::~MimicCliffStopEnemyNormal() = default;

bool MimicCliffStopEnemyNormal::init_(sead::Heap* heap) {
    return MimicCliffStopEnemyNormalBase::init_(heap);
}

void MimicCliffStopEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    MimicCliffStopEnemyNormalBase::enter_(params);
}

void MimicCliffStopEnemyNormal::leave_() {
    MimicCliffStopEnemyNormalBase::leave_();
}

void MimicCliffStopEnemyNormal::loadParams_() {
    MimicCliffStopEnemyNormalBase::loadParams_();
    getStaticParam(&mJumpDistXZ_s, "JumpDistXZ");
}

}  // namespace uking::ai
