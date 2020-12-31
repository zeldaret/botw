#include "Game/AI/AI/aiSiteBossSwordSeqThreeAI.h"

namespace uking::ai {

SiteBossSwordSeqThreeAI::SiteBossSwordSeqThreeAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSwordSeqThreeAI::~SiteBossSwordSeqThreeAI() = default;

bool SiteBossSwordSeqThreeAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossSwordSeqThreeAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossSwordSeqThreeAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossSwordSeqThreeAI::loadParams_() {
    getStaticParam(&mIsSkipLastAction_s, "IsSkipLastAction");
    getDynamicParam(&mIsResetEndTime_d, "IsResetEndTime");
    getDynamicParam(&mIsAttackPatternFixed_d, "IsAttackPatternFixed");
    getDynamicParam(&mIsNoCharge_d, "IsNoCharge");
    getDynamicParam(&mIsRestart_d, "IsRestart");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mOldTargetPos_d, "OldTargetPos");
}

}  // namespace uking::ai
