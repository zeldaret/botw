#include "Game/AI/AI/aiPullOutTree.h"

namespace uking::ai {

PullOutTree::PullOutTree(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PullOutTree::~PullOutTree() = default;

bool PullOutTree::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PullOutTree::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PullOutTree::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PullOutTree::loadParams_() {
    getStaticParam(&mTurnAng_s, "TurnAng");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
