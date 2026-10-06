#include "Game/Actor/AI/aiLastBossRecognizeRoot.h"

namespace uking::ai {

LastBossRecognizeRoot::LastBossRecognizeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossRecognizeRoot::~LastBossRecognizeRoot() = default;

bool LastBossRecognizeRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossRecognizeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastBossRecognizeRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossRecognizeRoot::loadParams_() {
    getStaticParam(&mAttackNum_s, "AttackNum");
    getStaticParam(&mAttackRandNum_s, "AttackRandNum");
    getStaticParam(&mWarpStartDist_s, "WarpStartDist");
    getStaticParam(&mForceWarpRetryDist_s, "ForceWarpRetryDist");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
}

}  // namespace uking::ai
