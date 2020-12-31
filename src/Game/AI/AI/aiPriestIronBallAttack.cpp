#include "Game/AI/AI/aiPriestIronBallAttack.h"

namespace uking::ai {

PriestIronBallAttack::PriestIronBallAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PriestIronBallAttack::~PriestIronBallAttack() = default;

bool PriestIronBallAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PriestIronBallAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PriestIronBallAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PriestIronBallAttack::loadParams_() {
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mShootPitchMin_s, "ShootPitchMin");
    getStaticParam(&mShootPitchMax_s, "ShootPitchMax");
    getStaticParam(&mNoise_s, "Noise");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
