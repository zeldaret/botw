#include "Game/AI/AI/aiNPCChasePlayerBlueFire.h"

namespace uking::ai {

NPCChasePlayerBlueFire::NPCChasePlayerBlueFire(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCChasePlayerBlueFire::~NPCChasePlayerBlueFire() = default;

bool NPCChasePlayerBlueFire::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCChasePlayerBlueFire::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCChasePlayerBlueFire::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCChasePlayerBlueFire::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mLeaveDist_s, "LeaveDist");
    getStaticParam(&mLostDist_s, "LostDist");
}

}  // namespace uking::ai
