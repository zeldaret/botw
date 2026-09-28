#include "Game/Actor/AI/aiBeamExplode.h"

namespace uking::ai {

BeamExplode::BeamExplode(const InitArg& arg) : SimpleBeamExplode(arg) {}

BeamExplode::~BeamExplode() = default;

bool BeamExplode::init_(sead::Heap* heap) {
    return SimpleBeamExplode::init_(heap);
}

void BeamExplode::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleBeamExplode::enter_(params);
}

void BeamExplode::leave_() {
    SimpleBeamExplode::leave_();
}

void BeamExplode::loadParams_() {
    SimpleBeamExplode::loadParams_();
}

}  // namespace uking::ai
