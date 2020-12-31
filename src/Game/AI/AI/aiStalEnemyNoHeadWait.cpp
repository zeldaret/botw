#include "Game/AI/AI/aiStalEnemyNoHeadWait.h"

namespace uking::ai {

StalEnemyNoHeadWait::StalEnemyNoHeadWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalEnemyNoHeadWait::~StalEnemyNoHeadWait() = default;

bool StalEnemyNoHeadWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalEnemyNoHeadWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void StalEnemyNoHeadWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalEnemyNoHeadWait::loadParams_() {
    getStaticParam(&mRebootDistance_s, "RebootDistance");
    getStaticParam(&mRebootTimer_s, "RebootTimer");
    getDynamicParam(&mIsExistLivingHead_d, "IsExistLivingHead");
    getDynamicParam(&mIsExistActiveActor_d, "IsExistActiveActor");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
