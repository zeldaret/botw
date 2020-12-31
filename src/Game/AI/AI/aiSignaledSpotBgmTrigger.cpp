#include "Game/AI/AI/aiSignaledSpotBgmTrigger.h"

namespace uking::ai {

SignaledSpotBgmTrigger::SignaledSpotBgmTrigger(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SignaledSpotBgmTrigger::~SignaledSpotBgmTrigger() = default;

bool SignaledSpotBgmTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SignaledSpotBgmTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SignaledSpotBgmTrigger::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SignaledSpotBgmTrigger::loadParams_() {
    getMapUnitParam(&mIsStopWithoutReductionY_m, "IsStopWithoutReductionY");
    getMapUnitParam(&mSound_m, "Sound");
}

}  // namespace uking::ai
