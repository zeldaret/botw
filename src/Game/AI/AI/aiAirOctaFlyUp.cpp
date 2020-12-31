#include "Game/AI/AI/aiAirOctaFlyUp.h"

namespace uking::ai {

AirOctaFlyUp::AirOctaFlyUp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AirOctaFlyUp::~AirOctaFlyUp() = default;

bool AirOctaFlyUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AirOctaFlyUp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AirOctaFlyUp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AirOctaFlyUp::loadParams_() {
    getStaticParam(&mFlyUpDuration_s, "FlyUpDuration");
    getDynamicParam(&mTargetDistance_d, "TargetDistance");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai
