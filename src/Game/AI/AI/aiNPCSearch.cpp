#include "Game/AI/AI/aiNPCSearch.h"

namespace uking::ai {

NPCSearch::NPCSearch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCSearch::~NPCSearch() = default;

bool NPCSearch::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCSearch::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCSearch::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCSearch::loadParams_() {
    getDynamicParam(&mIsHearing_d, "IsHearing");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTarget_d, "Target");
}

}  // namespace uking::ai
