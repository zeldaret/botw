#include "Game/AI/AI/aiWaitAndFaceLeader.h"

namespace uking::ai {

WaitAndFaceLeader::WaitAndFaceLeader(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WaitAndFaceLeader::~WaitAndFaceLeader() = default;

bool WaitAndFaceLeader::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WaitAndFaceLeader::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WaitAndFaceLeader::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WaitAndFaceLeader::loadParams_() {
    getStaticParam(&mTurnThreshold_s, "TurnThreshold");
    getDynamicParam(&mLeaderActor_d, "LeaderActor");
}

}  // namespace uking::ai
