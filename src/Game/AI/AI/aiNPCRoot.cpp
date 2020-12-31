#include "Game/AI/AI/aiNPCRoot.h"

namespace uking::ai {

NPCRoot::NPCRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCRoot::~NPCRoot() = default;

bool NPCRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCRoot::loadParams_() {
    getStaticParam(&mReleaseInterest2Time_s, "ReleaseInterest2Time");
    getStaticParam(&mPlayerHitVelocity_s, "PlayerHitVelocity");
    getStaticParam(&mStaggerUpperASName_s, "StaggerUpperASName");
    getStaticParam(&mStaggerUpperRunASName_s, "StaggerUpperRunASName");
}

}  // namespace uking::ai
