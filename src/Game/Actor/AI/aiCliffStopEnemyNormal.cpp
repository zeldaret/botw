#include "Game/Actor/AI/aiCliffStopEnemyNormal.h"

namespace uking::ai {

CliffStopEnemyNormal::CliffStopEnemyNormal(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CliffStopEnemyNormal::~CliffStopEnemyNormal() = default;

bool CliffStopEnemyNormal::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CliffStopEnemyNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CliffStopEnemyNormal::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CliffStopEnemyNormal::loadParams_() {
    getStaticParam(&mNoticeSoundTime_s, "NoticeSoundTime");
    getStaticParam(&mOffsetHand_s, "OffsetHand");
    getStaticParam(&mOffsetTail_s, "OffsetTail");
    getStaticParam(&mOffsetHandRotBase_s, "OffsetHandRotBase");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
    getAITreeVariable(&mIsCliffFreeze_a, "IsCliffFreeze");
}

}  // namespace uking::ai
