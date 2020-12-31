#include "Game/AI/AI/aiTargetLostCheck.h"

namespace uking::ai {

TargetLostCheck::TargetLostCheck(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetLostCheck::~TargetLostCheck() = default;

bool TargetLostCheck::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TargetLostCheck::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void TargetLostCheck::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TargetLostCheck::loadParams_() {
    getStaticParam(&mLostTimer_s, "LostTimer");
    getStaticParam(&mIsLostByScaffold_s, "IsLostByScaffold");
    getStaticParam(&mIsLostByTeached_s, "IsLostByTeached");
}

}  // namespace uking::ai
