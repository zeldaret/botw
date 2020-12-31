#include "Game/AI/AI/aiDefWanderAI.h"

namespace uking::ai {

DefWanderAI::DefWanderAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DefWanderAI::~DefWanderAI() = default;

void DefWanderAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DefWanderAI::loadParams_() {
    getStaticParam(&mFinishChangeCount_s, "FinishChangeCount");
    getStaticParam(&mChangeWaitRate_s, "ChangeWaitRate");
    getStaticParam(&mMaxWaitTime_s, "MaxWaitTime");
    getStaticParam(&mMinWaitTime_s, "MinWaitTime");
    getStaticParam(&mCheckWaitIsChangable_s, "CheckWaitIsChangable");
}

}  // namespace uking::ai
