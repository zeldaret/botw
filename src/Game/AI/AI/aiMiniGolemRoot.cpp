#include "Game/AI/AI/aiMiniGolemRoot.h"

namespace uking::ai {

MiniGolemRoot::MiniGolemRoot(const InitArg& arg) : GolemRootBase(arg) {}

MiniGolemRoot::~MiniGolemRoot() = default;

bool MiniGolemRoot::init_(sead::Heap* heap) {
    return GolemRootBase::init_(heap);
}

void MiniGolemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GolemRootBase::enter_(params);
}

void MiniGolemRoot::leave_() {
    GolemRootBase::leave_();
}

void MiniGolemRoot::loadParams_() {
    GolemRootBase::loadParams_();
    getStaticParam(&mLiftDeadTime_s, "LiftDeadTime");
    getAITreeVariable(&mIsAllowReactionLift_a, "IsAllowReactionLift");
}

}  // namespace uking::ai
