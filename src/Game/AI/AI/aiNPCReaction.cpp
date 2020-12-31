#include "Game/AI/AI/aiNPCReaction.h"

namespace uking::ai {

NPCReaction::NPCReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCReaction::~NPCReaction() = default;

void NPCReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCReaction::loadParams_() {
    getDynamicParam(&mReactionId_d, "ReactionId");
    getDynamicParam(&mIsReceiveInterest2_d, "IsReceiveInterest2");
    getDynamicParam(&mMessageId_d, "MessageId");
    getDynamicParam(&mGazeASName_d, "GazeASName");
    getDynamicParam(&mStaggerDir_d, "StaggerDir");
}

}  // namespace uking::ai
