#include "Game/AI/AI/aiSimpleLineBeam.h"

namespace uking::ai {

SimpleLineBeam::SimpleLineBeam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleLineBeam::~SimpleLineBeam() = default;

bool SimpleLineBeam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SimpleLineBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SimpleLineBeam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleLineBeam::loadParams_() {}

}  // namespace uking::ai
