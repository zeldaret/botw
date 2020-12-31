#include "Game/AI/AI/aiSunazarashiReturn.h"

namespace uking::ai {

SunazarashiReturn::SunazarashiReturn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SunazarashiReturn::~SunazarashiReturn() = default;

bool SunazarashiReturn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SunazarashiReturn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SunazarashiReturn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SunazarashiReturn::loadParams_() {
    getStaticParam(&mIsForceReturnHome_s, "IsForceReturnHome");
    getAITreeVariable(&mSunazarashiReturnPos_a, "SunazarashiReturnPos");
}

}  // namespace uking::ai
