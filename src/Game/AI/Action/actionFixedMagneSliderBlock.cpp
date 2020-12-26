#include "Game/AI/Action/actionFixedMagneSliderBlock.h"

namespace uking::action {

FixedMagneSliderBlock::FixedMagneSliderBlock(const InitArg& arg) : FixedMagneStick(arg) {}

FixedMagneSliderBlock::~FixedMagneSliderBlock() = default;

bool FixedMagneSliderBlock::init_(sead::Heap* heap) {
    return FixedMagneStick::init_(heap);
}

void FixedMagneSliderBlock::enter_(ksys::act::ai::InlineParamPack* params) {
    FixedMagneStick::enter_(params);
}

void FixedMagneSliderBlock::leave_() {
    FixedMagneStick::leave_();
}

void FixedMagneSliderBlock::loadParams_() {
    FixedMagneStick::loadParams_();
}

void FixedMagneSliderBlock::calc_() {
    FixedMagneStick::calc_();
}

}  // namespace uking::action
