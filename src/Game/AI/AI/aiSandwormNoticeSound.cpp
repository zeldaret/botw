#include "Game/AI/AI/aiSandwormNoticeSound.h"

namespace uking::ai {

SandwormNoticeSound::SandwormNoticeSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SandwormNoticeSound::~SandwormNoticeSound() = default;

bool SandwormNoticeSound::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SandwormNoticeSound::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SandwormNoticeSound::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SandwormNoticeSound::loadParams_() {
    getStaticParam(&mRetryDist_s, "RetryDist");
    getStaticParam(&mTargetActorLockOnDist_s, "TargetActorLockOnDist");
    getStaticParam(&mTargetPosLockOnDist_s, "TargetPosLockOnDist");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
