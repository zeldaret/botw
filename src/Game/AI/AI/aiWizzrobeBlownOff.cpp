#include "Game/AI/AI/aiWizzrobeBlownOff.h"

namespace uking::ai {

WizzrobeBlownOff::WizzrobeBlownOff(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WizzrobeBlownOff::~WizzrobeBlownOff() = default;

bool WizzrobeBlownOff::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WizzrobeBlownOff::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WizzrobeBlownOff::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WizzrobeBlownOff::loadParams_() {
    getStaticParam(&mDrownDepth_s, "DrownDepth");
    getStaticParam(&mIsForceGetUp_s, "IsForceGetUp");
}

}  // namespace uking::ai
