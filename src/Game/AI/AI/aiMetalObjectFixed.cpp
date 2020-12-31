#include "Game/AI/AI/aiMetalObjectFixed.h"

namespace uking::ai {

MetalObjectFixed::MetalObjectFixed(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MetalObjectFixed::~MetalObjectFixed() = default;

bool MetalObjectFixed::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MetalObjectFixed::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MetalObjectFixed::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MetalObjectFixed::loadParams_() {
    getMapUnitParam(&mIsFixedPlace_m, "IsFixedPlace");
}

}  // namespace uking::ai
