#include "Game/AI/AI/aiMagneSliderBlockRootThunder.h"

namespace uking::ai {

MagneSliderBlockRootThunder::MagneSliderBlockRootThunder(const InitArg& arg)
    : MagneShaftRootBase(arg) {}

MagneSliderBlockRootThunder::~MagneSliderBlockRootThunder() = default;

bool MagneSliderBlockRootThunder::init_(sead::Heap* heap) {
    return MagneShaftRootBase::init_(heap);
}

void MagneSliderBlockRootThunder::enter_(ksys::act::ai::InlineParamPack* params) {
    MagneShaftRootBase::enter_(params);
}

void MagneSliderBlockRootThunder::leave_() {
    MagneShaftRootBase::leave_();
}

void MagneSliderBlockRootThunder::loadParams_() {
    MagneShaftRootBase::loadParams_();
}

}  // namespace uking::ai
