#include "Game/AI/AI/aiBeamExplodeEitherHit.h"

namespace uking::ai {

BeamExplodeEitherHit::BeamExplodeEitherHit(const InitArg& arg) : BeamExplode(arg) {}

BeamExplodeEitherHit::~BeamExplodeEitherHit() = default;

bool BeamExplodeEitherHit::init_(sead::Heap* heap) {
    return BeamExplode::init_(heap);
}

void BeamExplodeEitherHit::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamExplode::enter_(params);
}

void BeamExplodeEitherHit::leave_() {
    BeamExplode::leave_();
}

void BeamExplodeEitherHit::loadParams_() {
    BeamExplode::loadParams_();
    getAITreeVariable(&mIsReflectThrownBullet_a, "IsReflectThrownBullet");
}

}  // namespace uking::ai
