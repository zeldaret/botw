#include "Game/AI/AI/aiBeamExplode.h"

namespace uking::ai {

BeamExplode::BeamExplode(const InitArg& arg) : BeamExplodeBase(arg) {}

BeamExplode::~BeamExplode() = default;

bool BeamExplode::init_(sead::Heap* heap) {
    return BeamExplodeBase::init_(heap);
}

void BeamExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    BeamExplodeBase::enter_(params);
}

void BeamExplode::leave_() {
    BeamExplodeBase::leave_();
}

void BeamExplode::loadParams_() {
    BeamExplodeBase::loadParams_();
}

}  // namespace uking::ai
