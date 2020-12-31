#include "Game/AI/AI/aiSpotBgmTrigger.h"

namespace uking::ai {

SpotBgmTrigger::SpotBgmTrigger(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SpotBgmTrigger::~SpotBgmTrigger() = default;

bool SpotBgmTrigger::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SpotBgmTrigger::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SpotBgmTrigger::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SpotBgmTrigger::loadParams_() {
    getMapUnitParam(&mIsStopWithoutReductionY_m, "IsStopWithoutReductionY");
    getMapUnitParam(&mSound_m, "Sound");
}

}  // namespace uking::ai
