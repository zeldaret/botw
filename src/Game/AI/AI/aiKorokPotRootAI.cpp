#include "Game/AI/AI/aiKorokPotRootAI.h"

namespace uking::ai {

KorokPotRootAI::KorokPotRootAI(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokPotRootAI::~KorokPotRootAI() = default;

bool KorokPotRootAI::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokPotRootAI::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KorokPotRootAI::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokPotRootAI::loadParams_() {
    getStaticParam(&mCrayLaunchSpeedRate_s, "CrayLaunchSpeedRate");
    getStaticParam(&mCrayLaunchAngularSpeed_s, "CrayLaunchAngularSpeed");
    getMapUnitParam(&mCrayLaunchSpeed_m, "CrayLaunchSpeed");
    getMapUnitParam(&mIsCrayShot_m, "IsCrayShot");
}

}  // namespace uking::ai
