#include "Game/AI/AI/aiNPCAttentionAI.h"

namespace uking::ai {

NPCAttentionAI::NPCAttentionAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCAttentionAI::~NPCAttentionAI() = default;

bool NPCAttentionAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCAttentionAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCAttentionAI::loadParams_() {
    getStaticParam(&mDurationTime_s, "DurationTime");
    getStaticParam(&mTurnAngleDiff_s, "TurnAngleDiff");
    getStaticParam(&mIsUseSight_s, "IsUseSight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
