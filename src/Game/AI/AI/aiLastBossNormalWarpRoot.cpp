#include "Game/AI/AI/aiLastBossNormalWarpRoot.h"

namespace uking::ai {

LastBossNormalWarpRoot::LastBossNormalWarpRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossNormalWarpRoot::~LastBossNormalWarpRoot() = default;

bool LastBossNormalWarpRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossNormalWarpRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastBossNormalWarpRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossNormalWarpRoot::loadParams_() {
    getStaticParam(&mIsKeepDisableDraw_s, "IsKeepDisableDraw");
    getStaticParam(&mSleepPartsActorName_s, "SleepPartsActorName");
    getDynamicParam(&mIsReturnHome_d, "IsReturnHome");
    getDynamicParam(&mIsForceWarp_d, "IsForceWarp");
    getDynamicParam(&mIsPartsActorTgOn_d, "IsPartsActorTgOn");
    getDynamicParam(&mIsPartsWarpEffectSync_d, "IsPartsWarpEffectSync");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
