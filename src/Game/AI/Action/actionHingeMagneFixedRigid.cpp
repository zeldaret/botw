#include "Game/AI/Action/actionHingeMagneFixedRigid.h"

namespace uking::action {

HingeMagneFixedRigid::HingeMagneFixedRigid(const InitArg& arg) : FixedMagneSliderBlock(arg) {}

HingeMagneFixedRigid::~HingeMagneFixedRigid() = default;

bool HingeMagneFixedRigid::init_(sead::Heap* heap) {
    return FixedMagneSliderBlock::init_(heap);
}

void HingeMagneFixedRigid::enter_(ksys::act::ai::InlineParamPack* params) {
    FixedMagneSliderBlock::enter_(params);
}

void HingeMagneFixedRigid::leave_() {
    FixedMagneSliderBlock::leave_();
}

void HingeMagneFixedRigid::loadParams_() {
    FixedMagneSliderBlock::loadParams_();
}

void HingeMagneFixedRigid::calc_() {
    FixedMagneSliderBlock::calc_();
}

}  // namespace uking::action
