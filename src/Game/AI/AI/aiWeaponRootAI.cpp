#include "Game/AI/AI/aiWeaponRootAI.h"

namespace uking::ai {

WeaponRootAI::WeaponRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WeaponRootAI::~WeaponRootAI() = default;

bool WeaponRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WeaponRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WeaponRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WeaponRootAI::loadParams_() {
    getStaticParam(&mBlinkFrame_s, "BlinkFrame");
    getStaticParam(&mFallOutSpeed_s, "FallOutSpeed");
    getStaticParam(&mLandNoiseLevel_s, "LandNoiseLevel");
    getMapUnitParam(&mIsFixedPlace_m, "IsFixedPlace");
    getMapUnitParam(&mIsEmitLandNoise_m, "IsEmitLandNoise");
}

}  // namespace uking::ai
