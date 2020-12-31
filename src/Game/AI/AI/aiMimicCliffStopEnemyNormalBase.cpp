#include "Game/AI/AI/aiMimicCliffStopEnemyNormalBase.h"

namespace uking::ai {

MimicCliffStopEnemyNormalBase::MimicCliffStopEnemyNormalBase(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

MimicCliffStopEnemyNormalBase::~MimicCliffStopEnemyNormalBase() = default;

bool MimicCliffStopEnemyNormalBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MimicCliffStopEnemyNormalBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MimicCliffStopEnemyNormalBase::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MimicCliffStopEnemyNormalBase::loadParams_() {
    getStaticParam(&mNoticeSoundTime_s, "NoticeSoundTime");
    getStaticParam(&mOffsetHand_s, "OffsetHand");
    getStaticParam(&mOffsetTail_s, "OffsetTail");
    getStaticParam(&mOffsetHandRotBase_s, "OffsetHandRotBase");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
    getAITreeVariable(&mIsCliffFreeze_a, "IsCliffFreeze");
}

}  // namespace uking::ai
